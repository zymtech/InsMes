#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

//注册协议
//客户端------>服务器
struct register_st {
    char account[32];
    char passwd[32];
};

#define RESPOND_RESUTL_OK       0
#define RESPOND_RESUTL_ERROR    1
//用户已经存在
#define ERROR_RESION_USER_EXISTS            0
//服务器----->客户端
struct respond_st {
    int result;
    int errno;
}; 
#endif




