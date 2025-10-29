#define HASH_SIZE 50//��ϣ��ĳ���
#define Name_SIZE 30//���ֱ���
#define R 49//С�ڹ�ϣ���ȵ�R
//int i,key;
struct Name {
	char *name;            //����
	int ascii;             //��Ӧ��ascii���
};
struct hash {
	char *name;            //����
	int ascii;             //��ӦASCII���
	int s;                 //���ҳ���
};
Name NameList [Name_SIZE];
hash hashtable [HASH_SIZE];
void init_Namelistlist ( );      //��ʼ��������
void C_hashtable ( ) ;      //����hash��
void collison (int i);          //��ͻ����,��i������������ͻ
void print_Namelist ( );
void print_hash ( );         //��ӡ����
#include<stdio.h>
#include<ctype.h>         //toascii����
void init_Namelist( ) {

	NameList[0].name="zhang";
	NameList[1].name="li";
	NameList[2].name="wang";
	NameList[3].name="huang";
	NameList[4].name="tie";
	NameList[5].name="chen";
	NameList[6].name="xu";
	NameList[7].name="zhou";
	NameList[8].name="tang";
	NameList[9].name="xia";
	NameList[10].name="hong";
	NameList[11].name="sha";
	NameList[12].name="da";
	NameList[13].name="yu";
	NameList[14].name="sao";
	NameList[15].name="yang";
	NameList[16].name="heng";
	NameList[17].name="feng";
	NameList[18].name="fen";
	NameList[19].name="zhi";
	NameList[20].name="lin";
	NameList[21].name="liu";
	NameList[22].name="tan";
	NameList[23].name="gong";
	NameList[24].name="hao";
	NameList[25].name="hua";
	NameList[26].name="shu";
	NameList[27].name="cheng";
	NameList[28].name="hang";
	NameList[29].name="wen";
	int i,j;
	for(i=0; i<Name_SIZE; i++) {
		for(j=0; (*(NameList[i].name+j))!='\0'; j++)
			NameList[i].ascii+=toascii(*(NameList[i].name+j));            //ascii�����
        NameList[i].ascii*=3;//����ֵ
	}
}
void collison (int i) {
	int key,flag;
	flag=0;                                                           //δ̽����ĩβ
	key=(NameList[i].ascii)%R;
	while(hashtable[key].s != 0) {
		key=key+1;
		//  printf("%d",key);                                             //����̽��ÿ�μ�1
		if(key==HASH_SIZE-1) {                                         //̽������ϣ��ĩ��
			key=0;
			flag=1;                                                    //̽����ĩβ��ʶ
		}
	}
	if(hashtable[key].s==0) {
		hashtable[key].name=NameList[i].name;
		hashtable[key].ascii=NameList[i].ascii;
		if(flag==0)
			hashtable[key].s= (key-(NameList[i].ascii%R))+1 ;
		else
			hashtable[key].s= (HASH_SIZE-(NameList[i].ascii%R))+key+1;   //���Ҵ���                                                                                       //���Ҵ���
	}
}
void C_hashtable() {                                    //������ϣ����
	int i,key;
	for(i=0; i<HASH_SIZE; i++) {
		hashtable[i].name="\0";
		hashtable[i].ascii=0;
		hashtable[i].s=0;                              //��ʼ����ϣ��
	}
	for(i=0; i<Name_SIZE; i++) {
		key=(NameList[i].ascii)%R;                        //����������
		if(hashtable[key].s == 0 ) {                    //δ������ͻ
			hashtable[key].name=NameList[i].name;
			hashtable[key].ascii=NameList[i].ascii;
			hashtable[key].s=1;
		} else                                              //������ͻ
			collison ( i );                                 //���ó�ͻ����

	}

}
void show() {
	printf("******************************Hashtable_creat******************************\n");
	printf("please input \n A:print Namelist \n B:print the hash table \n C:exit\n");
}
void print_Namelist ( ) {
	int i;
	for(i=0; i<Name_SIZE; i++) {
		printf("number:%d\tname:%s\tascii:%d\n",i,NameList[i].name,NameList[i].ascii);
	}
}
void print_hash ( ) {
	int i;
	float ASL=0.0;                         //ƽ�����ҳ���
	for(i=0; i<HASH_SIZE; i++) {
		printf("number:%d\tname:%s\tascii:%d\t%d\n",i,hashtable[i].name,hashtable[i].ascii,hashtable[i].s);
		ASL+=hashtable[i].s;
	}
	ASL=ASL/Name_SIZE;
	printf("ASL:%f\n",ASL);
}
int main() {
	char c;
	while(1) {
		show( );
		init_Namelist( );
		C_hashtable( );
		printf ("please in put the order: \n");
		scanf("%c",&c);
		getchar( );
		switch(c) {
			case 'A':
				print_Namelist ( );
				break;
			case 'B' :
				print_hash ( );
				break;
			case 'C' :
				break;
				// default: printf("EROOR\n");break;
		}
	}
	return 0;
}

