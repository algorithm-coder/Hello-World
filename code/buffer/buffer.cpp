 #include "buffer.h"

Buffer::Buffer(int initBuffSize) : buffer_(initBuffSize), readPos_(0), writePos_(0) {}

/* 可读数据的大小 */
size_t Buffer::ReadableBytes() const {  
    // 可读数据的大小 = 写位置 - 读位置
    return writePos_ - readPos_;
}

/* 后面可写数据的大小 */
size_t Buffer::WritableBytes() const {
    // 可写数据的大小 = 缓冲区的总大小 - 写位置
    return buffer_.size() - writePos_;
}

/* 前面可用空间大小 */
size_t Buffer::PrependableBytes() const {
    // 当前读取到哪个位置，就是前面可以用的空间大小
    return readPos_;
}

/* 可读数据地址 */
const char* Buffer::Peek() const {
    return BeginPtr_() + readPos_;
}

/* 将可读数据回收len位 */
void Buffer::Retrieve(size_t len) {
    assert(len <= ReadableBytes());
    readPos_ += len;
}

/* 将可读数据回收直到end位置 */
void Buffer::RetrieveUntil(const char* end) {
    assert(Peek() <= end );
    Retrieve(end - Peek());
}

/* 回收所有空间 */
void Buffer::RetrieveAll() {
    bzero(&buffer_[0], buffer_.size());
    readPos_ = 0;
    writePos_ = 0;
}

/* 回收并返回所有可读数据 */
std::string Buffer::RetrieveAllToStr() {
    std::string str(Peek(), ReadableBytes());
    RetrieveAll();
    return str;
}

/* 可写起始地址 */
const char* Buffer::BeginWriteConst() const {
    return BeginPtr_() + writePos_;
}
/* 可写起始地址 */
char* Buffer::BeginWrite() {
    return BeginPtr_() + writePos_;
}

/* 已写len长度，可写位置后移 */
void Buffer::HasWritten(size_t len) {
    writePos_ += len;
} 

/* 追加数据 */
void Buffer::Append(const std::string& str) {
    Append(str.data(), str.length());
}

/* 追加数据 */
void Buffer::Append(const void* data, size_t len) {
    assert(data);
    Append(static_cast<const char*>(data), len);
}

//  Append(buff, len - writable);   buff临时数组，len-writable是临时数组中的数据个数
/* 追加数据 */
void Buffer::Append(const char* str, size_t len) {
    assert(str);
    EnsureWriteable(len);
    std::copy(str, str + len, BeginWrite());
    HasWritten(len);
}

/* 追加数据 */
void Buffer::Append(const Buffer& buff) {
    Append(buff.Peek(), buff.ReadableBytes());
}

void Buffer::EnsureWriteable(size_t len) {
    if(WritableBytes() < len) {
        MakeSpace_(len);
    }
    assert(WritableBytes() >= len);
}

ssize_t Buffer::ReadFd(int fd, int* saveErrno) {
    
    char buff[65535];   // 临时的数组，保证能够把所有的数据都读出来
    
    struct iovec iov[2];
    const size_t writable = WritableBytes();
    
    /* 分散读， 保证数据全部读完 */
    iov[0].iov_base = BeginPtr_() + writePos_;
    iov[0].iov_len = writable;
    iov[1].iov_base = buff;
    iov[1].iov_len = sizeof(buff);

    const ssize_t len = readv(fd, iov, 2);
    if(len < 0) {
        *saveErrno = errno;
    }
    else if(static_cast<size_t>(len) <= writable) {
        writePos_ += len;
    }
    else {
        writePos_ = buffer_.size();
        Append(buff, len - writable);
    }
    return len;
}

ssize_t Buffer::WriteFd(int fd, int* saveErrno) {
    size_t readSize = ReadableBytes();
    ssize_t len = write(fd, Peek(), readSize);
    if(len < 0) {
        *saveErrno = errno;
        return len;
    } 
    readPos_ += len;
    return len;
}

/* 获取内存起始位置 */
char* Buffer::BeginPtr_() {
    return &*buffer_.begin();
}

/* 获取内存起始位置 */
const char* Buffer::BeginPtr_() const {
    return &*buffer_.begin();
}

/* 创建空间 */
void Buffer::MakeSpace_(size_t len) {
    // 原有剩余空间（前面+后面）不够，则在后面新加len的空间
    if (WritableBytes() + PrependableBytes() < len) {
        buffer_.resize(writePos_ + len + 1);
    }
    // 原有剩余空间（前面+后面）够，则挪动可读数据至最前面
    else {
        size_t readable = ReadableBytes();
        std::copy(BeginPtr_() + readPos_, BeginPtr_() + writePos_, BeginPtr_());
        readPos_ = 0;
        writePos_ = readPos_ + readable;
        assert(readable == ReadableBytes());
    }
}