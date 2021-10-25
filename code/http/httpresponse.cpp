/*
 * @Author       : mark
 * @Date         : 2020-06-27
 * @copyleft Apache 2.0
 */ 
#include "httpresponse.h"

using namespace std;

const unordered_map<string, string> HttpResponse::SUFFIX_TYPE = {
    { ".html",  "text/html" },
    { ".xml",   "text/xml" },
    { ".xhtml", "application/xhtml+xml" },
    { ".txt",   "text/plain" },
    { ".rtf",   "application/rtf" },
    { ".pdf",   "application/pdf" },
    { ".word",  "application/nsword" },
    { ".png",   "image/png" },
    { ".gif",   "image/gif" },
    { ".jpg",   "image/jpeg" },
    { ".jpeg",  "image/jpeg" },
    { ".au",    "audio/basic" },
    { ".mpeg",  "video/mpeg" },
    { ".mpg",   "video/mpeg" },
    { ".avi",   "video/x-msvideo" },
    { ".gz",    "application/x-gzip" },
    { ".tar",   "application/x-tar" },
    { ".css",   "text/css "},
    { ".js",    "text/javascript "},
};

const unordered_map<int, string> HttpResponse::CODE_STATUS = {
    { 200, "OK" },
    { 400, "Bad Request" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
};

const unordered_map<int, string> HttpResponse::CODE_PATH = {
    { 400, "/400.html" },
    { 403, "/403.html" },
    { 404, "/404.html" },
};

HttpResponse::HttpResponse() {
    code_ = -1;
    path_ = srcDir_ = "";
    isKeepAlive_ = false;
    mmFile_ = nullptr; 
    mmFileStat_ = { 0 };
};

HttpResponse::~HttpResponse() {
    UnmapFile();
}

void HttpResponse::Init(const string& srcDir, string& path, std::unordered_map<std::string, std::string> post, bool isKeepAlive, int code, bool isStatic){
    assert(srcDir != "");
    if (mmFile_) { UnmapFile(); }
    code_ = code;
    isKeepAlive_ = isKeepAlive;
    path_ = path;
    srcDir_ = srcDir;
    mmFile_ = nullptr; 
    mmFileStat_ = { 0 };
    post_ = post;
    isStatic_ = isStatic;
}

void HttpResponse::MakeResponse(Buffer& buff) {  
    /* 判断请求的资源文件 */
    if (stat((srcDir_ + path_).data(), &mmFileStat_) < 0 || S_ISDIR(mmFileStat_.st_mode)) {
        cout << "404 : !!!!!!! :" << srcDir_ + path_ << "!!"<< endl;
        code_ = 404;
    }
    else if (!(mmFileStat_.st_mode & S_IROTH)) {
        code_ = 403;
    }
    else if (code_ == -1) { 
        code_ = 200; 
    }
    
    ErrorHtml_();
    AddStateLine_(buff);
    AddHeader_(buff);
    AddContent_(buff);
}

char* HttpResponse::File() {
    return mmFile_;
}

size_t HttpResponse::FileLen() const {
    return mmFileStat_.st_size;
}

void HttpResponse::ErrorHtml_() {
    if (CODE_PATH.count(code_) == 1) {
        path_ = CODE_PATH.find(code_)->second;
        stat((srcDir_ + path_).data(), &mmFileStat_);
    }
}

void HttpResponse::AddStateLine_(Buffer& buff) {
    string status;
    if (CODE_STATUS.count(code_) == 1) {
        status = CODE_STATUS.find(code_)->second;
    }
    else {
        code_ = 400;
        status = CODE_STATUS.find(400)->second;
    }
    buff.Append("HTTP/1.1 " + to_string(code_) + " " + status + "\r\n");
}

void HttpResponse::AddHeader_(Buffer& buff) {
    buff.Append("Connection: ");
    if (isKeepAlive_) {
        buff.Append("keep-alive\r\n");
        buff.Append("keep-alive: max=6, timeout=120\r\n");
    } else {
        buff.Append("close\r\n");
    }
    buff.Append("Content-type: " + GetFileType_() + "\r\n");
}

void HttpResponse::AddContent_(Buffer& buff) {
    int srcFd = open((srcDir_ + path_).data(), O_RDONLY);
    if (srcFd < 0) { 
        ErrorContent(buff, "File NotFound!");
        return; 
    }
    LOG_DEBUG("file path %s", (srcDir_ + path_).data());
    // printf("enter AddContent\n");
    std::cout << path_ << std::endl;
    if (path_ == "/problem/1.html") {
        std::cout << "gggggg" << std::endl;
        isStatic_ = false;
    }
    /* 静态网站则直接传输文件即可，动态网站则需要在模板中添加数据 */
    if (isStatic_) {
        /* 将文件映射到内存提高文件的访问速度 
            MAP_PRIVATE 建立一个写入时拷贝的私有映射*/
        int* mmRet = (int*)mmap(0, mmFileStat_.st_size, PROT_READ, MAP_PRIVATE, srcFd, 0);
        if (*mmRet == -1) {
            ErrorContent(buff, "File NotFound!");
            return; 
        }
        mmFile_ = (char*)mmRet;
        buff.Append("Content-length: " + to_string(mmFileStat_.st_size) + "\r\n\r\n");
	    // cout << "enter static html constructor, path=" << srcDir_ + path_ << endl;
    }
    else {
	    // cout << "enter dynamic html constructor, path=" << srcDir_ + path_ << endl;
        
        if (path_ == "/problem/1.html") {
            int len1 = read(srcFd, DynamicResponseBuff, mmFileStat_.st_size);
            if (len1 == -1) {
                printf("DynamicResponseBuff read error\n");
            }

            string path = srcDir_ + "/md/test.md";
            int fd = open(path.data(), O_RDONLY);
            struct stat templateFileStat;
            stat(path.data(), &templateFileStat);
            char tmpBuff[65535];
            int len2 = read(fd, tmpBuff, templateFileStat.st_size);
            if (len2 == -1) {
                printf("DynamicResponseBuff read error\n");
            }
            string ans = "";
            for (int i = 0; i < len2; i++) {
                if (tmpBuff[i] == '\n') {
                    ans += "<br>";
                }
                else if (tmpBuff[i] == ' ') {
                    ans += "&nbsp;";
                }
                else if (tmpBuff[i] == '<') {
                    ans += "&lt;";
                }
                else if (tmpBuff[i] == '>') {
                    ans += "&gt;";
                }
                else {
                    ans += tmpBuff[i];
                }
            }
            strcpy(DynamicResponseBuff + len1, ans.c_str());
            len2 = ans.size();
            
            string path2 = srcDir_ + "/problem/2.html";
            int fd2 = open(path2.data(), O_RDONLY);
            struct stat templateFileStat2;
            stat (path2.data(), &templateFileStat2);
            int len3 = read(fd2, DynamicResponseBuff + len1 + len2, templateFileStat2.st_size);
            if (len3 == -1) {
                printf("DynamicResponseBuff read error\n");
            }

            DynamicResponseBuff[len1 + len2 + len3] = '\0';
            mmFile_ = DynamicResponseBuff;
            buff.Append("Content-length: " + to_string(len1 + len2 + len3) + "\r\n\r\n");
            mmFileStat_.st_size = len1 + len2 + len3;
            close(fd2);
            close(fd);
        }
        else {
            int len1 = read(srcFd, DynamicResponseBuff, mmFileStat_.st_size);
            if (len1 == -1) {
                printf("DynamicResponseBuff read error\n");
            }

            string tmp = "<html> <script> var name='" + post_["username"] + "';\n";
            strcpy(DynamicResponseBuff + len1, tmp.c_str());
            int len2 = tmp.size();

            string path = srcDir_ + "template.text";
            int fd = open(path.data(), O_RDONLY);
            struct stat templateFileStat;
            stat (path.data(), &templateFileStat);
            int len3 = read(fd, DynamicResponseBuff + len1 + len2, templateFileStat.st_size);
            if (len3 == -1) {
                printf("DynamicResponseBuff read error\n");
            }

            DynamicResponseBuff[len1 + len2 + len3] = '\0';
            mmFile_ = DynamicResponseBuff;
            buff.Append("Content-length: " + to_string(len1 + len2 + len3) + "\r\n\r\n");
            mmFileStat_.st_size = len1 + len2 + len3;
            close(fd);
	}

    }
}

void HttpResponse::UnmapFile() {
    if(mmFile_) {
        munmap(mmFile_, mmFileStat_.st_size);
        mmFile_ = nullptr;
    }
}

string HttpResponse::GetFileType_() {
    /* 判断文件类型 */
    string::size_type idx = path_.find_last_of('.');
    if (idx == string::npos) {
        return "text/plain";
    }
    string suffix = path_.substr(idx);
    if (SUFFIX_TYPE.count(suffix) == 1) {
        return SUFFIX_TYPE.find(suffix)->second;
    }
    return "text/plain";
}

void HttpResponse::ErrorContent(Buffer& buff, string message) {
    string body;
    string status;
    body += "<html><title>Error</title>";
    body += "<body bgcolor=\"ffffff\">";
    if(CODE_STATUS.count(code_) == 1) {
        status = CODE_STATUS.find(code_)->second;
    } else {
        status = "Bad Request";
    }
    body += to_string(code_) + " : " + status  + "\n";
    body += "<p>" + message + "</p>";
    body += "<hr><em>TinyWebServer</em></body></html>";

    buff.Append("Content-length: " + to_string(body.size()) + "\r\n\r\n");
    buff.Append(body);
}
