//http://blog.livedoor.jp/akf0/archives/51585502.html

#include <stdio.h>

#include <winsock2.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <time.h>


int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力

	char destination[20];
	printf("adress=");
	scanf("%s",destination);
	dest.sin_addr.s_addr = inet_addr(destination);

	char port[6];
	printf("port=");
	scanf("%s",port);
	dest.sin_port = htons(atoi(port));


	//char destination[] = "127.0.0.1";  //アドレス

	//dest.sin_port = htons(12345);  //ポート番号

	dest.sin_family = AF_INET;

	//dest.sin_addr.s_addr = inet_addr(destination);



	//ソケット通信の準備・生成

	WSADATA data;

	WSAStartup(MAKEWORD(2, 0), &data);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);



	//サーバへの接続

	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {

		printf("%sに接続できませんでした\n", destination);

		return -1;

	}

	printf("%sに接続しました\n", destination);


	//char msg[] = "Hello Server!";
	//char buffer[1024];
	char buffer[1024];
	char name[] = "name:SAMPLE\n";
	char move1[] = "move:300\n";
	char move2[] = "move:500\n";
	char move3[] = "move:700\n";
	char cannon1[] = "cannon:300\n";
	char cannon2[] = "cannon:500\n";	
	char cannon3[] = "cannon:700\n";
	char search1[] = "search:300\n";
	char search2[] = "search:500\n";	
	char search3[] = "search:700\n";
	char state1[] = "state:hp\n";
	char state2[] = "state:hight\n";	
	char state3[] = "state:cannon\n";	
	
	//サーバにデータを送信：名前の送信
	send(s, name, strlen(name), 0);
	
	//サーバからデータを受信：nameの返信 を受け取る
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s\n\n", buffer);

	//サーバからデータを受信：START を受け取る
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s\n\n", buffer);


	int flag = 0;
	time_t t = time(NULL);
	srand(t);

while(1){
	
	flag = rand() % 3;


	if(flag==0){
		
		//サーバにデータを送信 移動指令
		send(s, move1, strlen(move1), 0);
		
	}else if(flag==1){
		
		//サーバにデータを送信 移動指令
		send(s, move2, strlen(move2), 0);
		
	}else if(flag==2){
		
		//サーバにデータを送信 移動指令
		send(s, move3, strlen(move3), 0);
		
	}


	//サーバから返信データを受信
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s", buffer);
	
	
	Sleep(1000*(rand()%3+1));
	
	
	
	flag = rand() % 3;
	

	if(flag==0){
		
		//サーバにデータを送信 移動指令
		send(s, cannon1, strlen(cannon1), 0);
		
	}else if(flag==1){
		
		//サーバにデータを送信 移動指令
		send(s, cannon2, strlen(cannon2), 0);
		
	}else if(flag==2){
		
		//サーバにデータを送信 移動指令
		send(s, cannon3, strlen(cannon3), 0);
		
	}


	//サーバから返信データを受信
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s", buffer);

	Sleep(1000*(rand()%3+1));


	if(flag==0){
		
		//サーバにデータを送信 移動指令
		send(s, search1, strlen(search1), 0);
		
	}else if(flag==1){
		
		//サーバにデータを送信 移動指令
		send(s, search2, strlen(search2), 0);
		
	}else if(flag==2){
		
		//サーバにデータを送信 移動指令
		send(s, search3, strlen(search3), 0);
		
	}
	
	//サーバから返信データを受信
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s", buffer);
	
	if(flag==0){
		
		//サーバにデータを送信 移動指令
		send(s, state1, strlen(state1), 0);
		
	}else if(flag==1){
		
		//サーバにデータを送信 移動指令
		send(s, state2, strlen(state2), 0);
		
	}else if(flag==2){
		
		//サーバにデータを送信 移動指令
		send(s, state3, strlen(state3), 0);
		
	}
	
	//サーバから返信データを受信
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s", buffer);

}







	//サーバにデータを送信

	//send(s, "Hello Server!", strlen(msg), 0);



	//サーバからデータを受信

	//recv(s, buffer, 1024, 0);

	//printf("→ %s\n\n", buffer);



	// Windows でのソケットの終了

	closesocket(s);

	WSACleanup();



	return 0;

}