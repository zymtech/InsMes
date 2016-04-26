package com.embsky;
//java调用C语言函数的步骤
//1.规划 
//2.做库
// javac com/embsky/Hello.java
// javah -jni com.embsky.Hello
// mv com_embsky_Hello.h channel.c
// 修改channel.c的代码（参考老师代码）
// gcc -c -fPIC channel.c 
// gcc -shared -o libchannel.so channel.o
// cp libchannel.so /lib
public class Hello {
	//申明本地方法 C/C++
	//本地方法名字中不能有下划线
	static native void selectChannel(int channel_no);

	static {
		// /lib/libchannel.so 动态库
		System.loadLibrary("channel");
	}

	public static void main(String[] args) {
		System.out.println("helloworld");	
		selectChannel(3);
	}
}



