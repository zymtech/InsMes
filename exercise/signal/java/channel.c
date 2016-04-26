#include <jni.h>

//C语言函数
JNIEXPORT void JNICALL Java_com_embsky_Hello_selectChannel
  (JNIEnv *env, jclass obj, jint channel_no)
{
	printf("选择的频道是%d\n", channel_no);
}

