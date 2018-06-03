#include "../Headers/httphdr.hpp"

#define TERMINATOR "\r\n"

void httphdr::generate_unterminated() {
    *hdr = method + " /" + path + " HTTP/1.0" + TERMINATOR
             + "User-Agent: " + useragent + TERMINATOR
             + "Cache-Control: " + cache_control + TERMINATOR
             + "Accept-Encoding: " + encoding + TERMINATOR
             + "Accept-Charset: " + charset[0] + ", " + charset[1] + TERMINATOR
             + "Referer: " + referer + TERMINATOR
             + "Accept: " + accept + TERMINATOR
             + "Connection: " + connection_type + TERMINATOR
             + "Content-Type: " + content_type + TERMINATOR
             + (content_length ? "Content-Length: " + std::to_string(content_length) : "") + TERMINATOR
             + "Cookie: " + cookie[0] + "=" + cookie[1] + TERMINATOR
             + "Keep-Alive: " + std::to_string(keep_alive) + TERMINATOR
             + "DNT: " + std::to_string(DNT) + TERMINATOR;
}

void httphdr::generate() {
    generate_unterminated();
    *hdr += TERMINATOR;
}

const char *httphdr::get() {
    return hdr->c_str();
}

unsigned long httphdr::length() {
    return hdr->length();
}

httphdr& httphdr::operator=(std::string& header) noexcept{
    *hdr = header;
    return *this;
}

httphdr& httphdr::operator=(httphdr&& header) noexcept{
    method = header.method;
    path = header.path;
    useragent = header.useragent;
    cache_control = header.cache_control;
    encoding = header.encoding;
    charset = header.charset;
    referer = header.referer;
    content_type = header.content_type;
    cookie = header.cookie;
    connection_type = header.connection_type;
    keep_alive = header.keep_alive;
    DNT = header.DNT;
    accept = header.accept;
    content_length = header.content_length;
    *hdr = *header.get();
    return *this;
}

httphdr::httphdr() {
    hdr = new std::string{};
}

httphdr::~httphdr() {
    delete hdr;
}
