#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<graphics.h>   //easyxͼ��
#include<easyx.h>   //easyxͼ��

#define PATH1 "����������Ϣ��.csv"
#define PATH2 "����������Ϣ��.csv"
#define PATH3 "�⳵������Ϣ��.csv"
#define PATH4 "����������Ϣ��ѯ���.csv"
#define PATH5 "�⳵������Ϣ��ѯ���.csv"
#define PATH01 "����������Ϣ��.dat"
#define PATH02 "����������Ϣ��.dat"
#define PATH03 "�⳵������Ϣ��.dat"
#define TURE 1
#define OK 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -1
typedef int status;  //״̬����ֵ

/*����������Ϣ��*/
struct cla_node {
public:
	char car_code;  //�������ͱ���
	char car_type[20];
	int car_remain;
	struct cla_node* cla_next;
	struct inf_node* inf_next;
}cla_node, * cla_list;

/*����������Ϣ��*/
struct inf_node {
public:
	int car_number;  //�������
	char car_license_plate_number[10];
	char car_code;
	char car_name[20];
	char gear_way[10];
	float fee_daily;
	char car_status;
	struct inf_node* inf_next;
	struct rent_node* rent_next;

}inf_node, * inf_list;

/*�⳵������Ϣ��*/
struct rent_node {
public:
	char rent_number[20];
	char person_id[20];
	char person_name[20];
	char person_phone[20];
	int car_number;	
	char date_take[18];
	char date_return_schedule[18];
	float deposit;//Ѻ�� =�������*5
	char date_return_actually[18];
	float fee_total_schedule;
	float fee_total_actually;
	struct rent_node* rent_next;
}rent_node, * rent_list;

/*�ļ�����*/
//���복��������Ϣ headΪͷ���ָ�� pathΪ·��
status get_from_csv1(cla_list* head, char* path) {
	cla_list p = *head;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("δ�ܴ��ļ�\n");
		return ERROR;
	}
	fgets(tmp_buf, sizeof(tmp_buf), fp);
	while (fgets(tmp_buf, sizeof(tmp_buf), fp) > 0) {
		if (p->cla_next == NULL) {
			p->cla_next = (cla_list)malloc(sizeof(cla_node));
			p = p->cla_next;
			p->cla_next = NULL;
			p->inf_next = NULL;
		}
		tmp_buf[1023] = 0;
		char* temp = strtok(tmp_buf, ",");
		char* temp1 = strtok(NULL, ",");
		char* temp2 = strtok(NULL, ",");
		p->car_code = temp[0];
		strcpy(p->car_type, temp1);
		p->car_remain = atoi(temp2);
		memset(tmp_buf, 0, sizeof(tmp_buf));/*���temp_buf*/
	}
	fclose(fp);
	return OK;
}

//���복��������Ϣ�� headΪͷ���ָ�� pathΪ·��
status get_from_csv2(cla_list* head, char* path) {//���복��������Ϣ��
	cla_list p = (*head)->cla_next;
	inf_list p_inf = (inf_list)malloc(sizeof(inf_node));;
	inf_list t = NULL;
	p->inf_next = p_inf;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("δ�ܴ��ļ�\n");
		return ERROR;
	}
	fgets(tmp_buf, sizeof(tmp_buf), fp);
	while (fgets(tmp_buf, sizeof(tmp_buf), fp) > 0) {
		tmp_buf[1023] = 0;
		char* temp = strtok(tmp_buf, ",");
		char* temp1 = strtok(NULL, ",");
		char* temp2 = strtok(NULL, ",");
		char* temp3 = strtok(NULL, ",");
		char* temp4 = strtok(NULL, ",");
		char* temp5 = strtok(NULL, ",");
		char* temp6 = strtok(NULL, ",");
		if ( temp2[0] != p->car_code ) {//��һ�೵��������
			free(t->inf_next);
			t->inf_next = NULL;
			if ( p->cla_next == NULL ) return ERROR;
			p = p->cla_next;
			p_inf = (inf_list)malloc(sizeof(inf_node));
			p->inf_next = p_inf;
	}
		p_inf->inf_next = NULL;
		p_inf->rent_next = NULL;
		p_inf->car_number = atoi(temp);
		strcpy(p_inf->car_license_plate_number, temp1);
		p_inf->car_code = temp2[0];
		strcpy(p_inf->car_name, temp3);
		strcpy(p_inf->gear_way, temp4);
		p_inf->fee_daily = atof(temp5);
		p_inf->car_status = temp6[0];
		t = p_inf;
		p_inf->inf_next = (inf_list)malloc(sizeof(inf_node));
		p_inf =p_inf->inf_next;
		memset(tmp_buf, 0, sizeof(tmp_buf));/*���temp_buf*/
	}
	free(t->inf_next);
	t->inf_next = NULL;
	fclose(fp);
	return OK;
}

//�����⳵������Ϣ�� headΪͷ���ָ�� pathΪ·��
status get_from_csv3(cla_list* head, char* path) {//�����⳵������Ϣ��
	cla_list p = (*head)->cla_next;
	inf_list p_inf = p->inf_next;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("δ�ܴ��ļ�\n");
		return ERROR;
	}
	fgets(tmp_buf, sizeof(tmp_buf), fp);
	while (fgets(tmp_buf, sizeof(tmp_buf), fp) > 0) {
		tmp_buf[1023] = 0;
		char* temp = strtok(tmp_buf, ",");
		char* temp1 = strtok(NULL, ",");
		char* temp2 = strtok(NULL, ",");
		char* temp3 = strtok(NULL, ",");
		char* temp4 = strtok(NULL, ",");
		char* temp5 = strtok(NULL, ",");
		char* temp6 = strtok(NULL, ",");
		char* temp7 = strtok(NULL, ",");
		char* temp8 = strtok(NULL, ",");
		char* temp9 = strtok(NULL, ",");
		char* temp10 = strtok(NULL, ",");
		p = (*head)->cla_next;
		p_inf = p->inf_next;
		 do{
			 if (p_inf == NULL) {  //�л���һ�೵
				 p = p->cla_next;
				 p_inf = p->inf_next;
				 continue;
			 }
			 if (p_inf->car_number == atoi(temp4)) break;  //�ҵ���Ӧ��ų���
			p_inf = p_inf->inf_next;
		 } while (p!=NULL);
		 rent_list r=p_inf->rent_next;
		 rent_list t;
		 while (r != NULL) {
			 t = r; r = r->rent_next;
		 }
		 r = (rent_list)malloc(sizeof(rent_node));
		 r->rent_next = NULL;
		 if (p_inf->rent_next == NULL) p_inf->rent_next = r;
		 else 		 t->rent_next = r;
		 strcpy(r->rent_number,temp);
		 strcpy(r->person_id,temp1);
		 strcpy(r->person_name,temp2);
		 strcpy(r->person_phone,temp3);
		 r->car_number = atoi(temp4);
		 strcpy(r->date_take, temp5);
		 strcpy(r->date_return_schedule, temp6);
		 r->deposit = atof(temp7);
		 strcpy(r->date_return_actually, temp8);
		 r->fee_total_schedule = atof(temp9);
		 r->fee_total_actually = atof(temp10);
		 memset(tmp_buf, 0, sizeof(tmp_buf));/*���temp_buf*/
	}
	fclose(fp);
	return OK;
}

/*�������ļ�*/
//����������������Ϣ��.csv     headΪͷ���ָ�� pathΪ·��
status write_to_csv1(cla_list* head, char* path){
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w+");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "�������ͱ���,������������,�������\n");
	while (p != NULL) {
		fprintf(f, "%c,%s,%d\n", p->car_code, p->car_type, p->car_remain);
		p = p->cla_next;
	}
	printf("-----------------------------�ѵ�����%s----------------------------\n", path);
	fclose(f);
	return OK;
}
//����������������Ϣ��.csv      headΪͷ���ָ�� pathΪ·��
status write_to_csv2(cla_list* head, char* path){
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "�������,���ƺ�,�������ͱ���,��������,�ŵ���ʽ,ÿ�����Ԫ��,����״̬\n");
	while (p != NULL) {
		inf_list p_inf = p->inf_next;
		while (p_inf != NULL) {
			fprintf(f, "%d,%s,%c,%s,%s,%f,%c\n", p_inf->car_number, p_inf->car_license_plate_number, p_inf->car_code, p_inf->car_name, p_inf->gear_way, p_inf->fee_daily, p_inf->car_status);
			p_inf = p_inf->inf_next;
		}
		p = p->cla_next;
	}
	printf("-----------------------------�ѵ�����%s----------------------------\n", path);
	fclose(f);
	return OK;
}

//�������⳵������Ϣ��.csv    headΪͷ���ָ�� pathΪ·��
status write_to_csv3(cla_list* head, char* path) {
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "�������,���֤��,��������,�ֻ�����,���ó������,ȡ��ʱ��,ԤԼ����ʱ��,Ѻ��Ԫ��,ʵ�ʻ���ʱ��,Ӧ�ɷ��ã�Ԫ��,ʵ�ɷ��ã�Ԫ��\n");
	while (p != NULL) {
		inf_list p_inf = p->inf_next;
		while (p_inf != NULL) {
			rent_list p_rent = p_inf->rent_next;
			while (p_rent != NULL) {
				fprintf(f, "%s,%s,%s,%s,%d,%s,%s,%f,%s,%f,%f\n", p_rent->rent_number, p_rent->person_id, p_rent->person_name, p_rent->person_phone, p_rent->car_number,
					p_rent->date_take, p_rent->date_return_schedule, p_rent->deposit, p_rent->date_return_actually, p_rent->fee_total_schedule, p_rent->fee_total_actually);
				p_rent = p_rent->rent_next;
			}
			p_inf = p_inf->inf_next;
		}
		p = p->cla_next;
	}
	printf("-----------------------------�ѵ�����%s----------------------------\n", path);
	fclose(f);
	return OK;
}

/*��������������*/
status in_cla(cla_list* head) {
	cla_list h = *head;
	while (h->cla_next != NULL) {
		h = h->cla_next;
	}
	h->cla_next = (cla_list)malloc(sizeof(cla_node));
	h = h->cla_next;
	printf("��������\n�������(����)������(�羭����)���������(����)  �ո����\n");
	scanf("%c %s %d", &h->car_code, h->car_type, &h->car_remain);
	getchar();
	h->cla_next = NULL;
	h->inf_next = NULL;
	return OK;
}

/*�޸ĳ�������*/
status mod_cla(cla_list* head, char c) {
	cla_list p = (*head)->cla_next;
	while (p != NULL && p->car_code != c) {
		p = p->cla_next;
	}
	if (p != NULL) {
		//	memset(p->car_type, 0, sizeof(p->car_type));		//����ַ����飨���࣡��
		printf("��ȫ�������޸�(������ţ����ͣ��������)��");
		scanf("%c %s %d", &p->car_code, p->car_type, &p->car_remain);
		getchar();
	}
	else {
		printf("û���ҵ�\n");
		return ERROR;
	}
	return OK;
}

/*ɾ���������ಢ�ͷſռ�*/
status del_cla(cla_list* head, char c) {
	cla_list p = *head;
	while (p->cla_next != NULL && p->cla_next->car_code != c) {
		p = p->cla_next;
	}
	if (p->cla_next->car_code == c) {
		cla_list t = p->cla_next;
		p->cla_next = p->cla_next->cla_next;
		free(t);
	}
	else
		return ERROR;
	return OK;
}

/*��ʾĿǰ�ĳ���������Ϣ*/
void show_cla(cla_list h) {
	cla_list p = h->cla_next;
	printf("---------------------------------����������Ϣ----------------------------------\n");
	printf("�������            ����                ���\n");
	while (p != NULL) {
		printf("%-20c%-20s%-20d\n", p->car_code, p->car_type, p->car_remain);
		p = p->cla_next;
	}
}

/*��������������Ϣ���*/
status in_inf(cla_list* head) {
	inf_list p = (*head)->inf_next;
	inf_list t = (inf_list)malloc(sizeof(inf_node));
	if (p == NULL) {
		(*head)->inf_next = t;
	}
	else {
		while (p->inf_next != NULL) {
			p = p->inf_next;
		}
		p->inf_next = t;
	}
	printf("�������복����  ��ţ����ƺţ��������ƣ��ŵ���ʽ��ÿ����𣬳���״̬��y/n)  �ո����\n");
	scanf("%d %s %s %s %f %c", &t->car_number, t->car_license_plate_number, t->car_name, t->gear_way, &t->fee_daily, &t->car_status);
	getchar();
	t->car_code = (*head)->car_code;
	t->inf_next = NULL;
	t->rent_next = NULL;
	return OK;
}

/*�޸ĳ���������Ϣ*/
status mod_inf(cla_list* head, int num) {
	inf_list p = (*head)->inf_next;
	while (p != NULL && p->car_number != num) {
		p = p->inf_next;
	}
	if (p != NULL) {
		printf("����������ó���������Ϣ��");
		printf("�������복����  ��ţ����ƺţ��������ƣ��ŵ���ʽ��ÿ����𣬳���״̬��y/n)\n");
		scanf("%d %s %s %s %f %c", &p->car_number, p->car_license_plate_number, p->car_name, p->gear_way, &p->fee_daily, &p->car_status);
		getchar();
	}
	else {
		printf("û�иñ�ų���!\n");
		return ERROR;
	}
	return OK;
}

/*ɾ������������Ϣ���ͷſռ�*/
status del_inf(cla_list* head, int num) {
	if ((*head)->inf_next == NULL)
		return ERROR;
	if ((*head)->inf_next->car_number == num) {
		inf_list t = (*head)->inf_next;
		(*head)->inf_next = (*head)->inf_next->inf_next;
		free(t);
		return OK;
	}
	inf_list p = (*head)->inf_next;
	while (p->inf_next != NULL && p->inf_next->car_number != num) {
		p = p->inf_next;
	}
	if (p->inf_next != NULL) {
		inf_list t = p->inf_next;
		p->inf_next = p->inf_next->inf_next;
		free(t);
	}
	return OK;
}

/*��ʾĿǰ����������Ϣ*/
void show_inf(cla_list h) {
	inf_list t = h->inf_next;
	printf("��ǰ���г������£�\n"); printf("��� ���ƺ�                �������ͱ���     ��������            �ŵ���ʽ           ÿ�����   ����״̬��y/n):\n");
	while (t != NULL) {
		printf("%-5d %-20s %-15c %-20s %-20s %-10.1f %-c\n", t->car_number, t->car_license_plate_number, t->car_code, t->car_name, t->gear_way, t->fee_daily, t->car_status);
		t = t->inf_next;
	}
}

/*�����⳵������Ϣ���*/
status in_rent(inf_list* head) {
	int d_sch, d_real;
	rent_list p = (*head)->rent_next;
	rent_list t = (rent_list)malloc(sizeof(rent_node));
	if (p == NULL) { (*head)->rent_next = t; }
	else {
		while (p->rent_next != NULL) p = p->rent_next;
		p->rent_next = t;
	}
	printf("�������붩����ţ��������������֤�ţ��ֻ����룬ȡ��ʱ�䣬ԤԼ����ʱ�䣬ʵ�ʻ���ʱ�䣨0��ʾδ�黹�� �ո����\n");
	scanf("%s %s %s %s %s %s %s", t->rent_number, t->person_name, t->person_id, t->person_phone,
		t->date_take, t->date_return_schedule, t->date_return_actually);
	t->car_number = (*head)->car_number;
	d_sch = 10 * t->date_return_schedule[8] + t->date_return_schedule[9] - 10 * t->date_take[8] - t->date_take[9];
	t->fee_total_schedule = d_sch * (*head)->fee_daily;
	t->deposit = 5 * t->fee_total_schedule;
	if (t->date_return_actually[0] != '0') {
		d_real = 10 * t->date_return_actually[8] + t->date_return_actually[9] - 10 * t->date_take[8] - t->date_take[9];
		if (d_real > d_sch) { t->fee_total_actually = d_real * (*head)->fee_daily; }
		else { t->fee_total_actually = d_sch * (*head)->fee_daily; }
	}
	t->rent_next = NULL;
	return OK;
}

/*�޸��⳵������Ϣ*/
status mod_rent(inf_list* head, char rt[]) {
	rent_list t = (*head)->rent_next;
	while (t != NULL && strcmp(t->rent_number, rt) != 0) { t = t->rent_next; }
	if (t != NULL) {
		printf("���������붩����Ϣ\n");
		printf("�������붩����ţ��������������֤�ţ��ֻ����룬ȡ��ʱ�䣬ԤԼ����ʱ�䣬ʵ�ʻ���ʱ�䣨0��ʾδ�黹��\n");
		scanf("%s %s %s %s %s %s %s", t->rent_number, t->person_name, t->person_id, t->person_phone,
			t->date_take, t->date_return_schedule, t->date_return_actually);
	}
	else {
		printf("û�и��⳵������\n");
		return ERROR;
	}
	return OK;
}

/*ɾ���⳵������Ϣ���ͷſռ�*/
status del_rent(inf_list* head, char rt[]) {
	if ((*head)->rent_next == NULL)
		return ERROR;
	if (strcmp((*head)->rent_next->rent_number, rt) == 0) {
		free((*head)->rent_next);
		(*head)->rent_next = NULL;
		return OK;
	}
	rent_list p = (*head)->rent_next;
	while (p->rent_next != NULL && strcmp(p->rent_next->rent_number, rt) != 0) {
		p = p->rent_next;
	}
	if (p->rent_next != NULL) {
		rent_list t = p->rent_next;
		p->rent_next = p->rent_next->rent_next;
		free(t);
	}
	return OK;
}

/*��ʾĿǰ�����⳵������Ϣ*/
void show_rent(inf_list h) {
	rent_list p = h->rent_next;
	printf("��ǰ���������ж������£�\n");
	printf("�������    ���֤��         ��������     �ֻ�����       ���ó������      ȡ��ʱ��        ԤԼ����ʱ��       Ѻ��     ʵ�ʻ���ʱ��     Ӧ�ɷ���    ʵ�ɷ���\n");
	while (p != NULL) {
		printf("%-10s%-20s%-10s%-20s%-10d%-20s%-20s%-10.1f%-20s%-10.1f%-10.1f\n", p->rent_number, p->person_id, p->person_name, p->person_phone, p->car_number, p->date_take,
			p->date_return_schedule, p->deposit, p->date_return_actually, p->fee_total_schedule, p->fee_total_actually);
		p = p->rent_next;
	}
}

/*�ͷ��ڴ�ռ�*/
void free_cla(cla_list* head) {
	cla_list p = NULL;
	inf_list pi = NULL;
	rent_list pr = NULL;
	rent_list tr = NULL;
	while ((*head)->cla_next != NULL) {
		p = (*head)->cla_next;
		while (p->inf_next != NULL) {
			pi = p->inf_next;
			while (pi->rent_next != NULL) {
				tr = pi->rent_next;
				pi->rent_next = pi->rent_next->rent_next;
				free(tr);
			}
			p->inf_next = p->inf_next->inf_next;
			free(pi);
		}
		(*head)->cla_next = (*head)->cla_next->cla_next;
		free(p);
	}
	free(*head);
	*head = NULL;
}

/*������*/
int main() {

	char path1[30] = { PATH1 };
	char path2[30] = { PATH2 };
	char path3[30] = { PATH3 };
	char path4[30] = { PATH4 };
	char path5[30] = { PATH5 };
	char path01[30] = { PATH01 };
	char path02[30] = { PATH02 };
	char path03[30] = { PATH03 };
	char pathwrite[50];
	char pathget[50];
	char op;
	cla_list head = (cla_list)malloc(sizeof(cla_node));
	if (head == NULL) {
		printf("��ʼ����ͷ����\n");
		return 0;
	}
	head->cla_next = NULL;
	head->inf_next = NULL;

	/*�Զ�����*/
	if (get_from_csv1(&head, path01) == OK && get_from_csv2(&head, path02) == OK && get_from_csv3(&head, path03)) {
		printf("------------------------------------------------------------------------------\n");
		printf("-----------------------------�ϴ�dat����������--------------------------------\n");
	}
	else {
		printf("�����ļ�ʧ�ܣ������ļ�\n");
		return ERROR;
	}

	/*���˵�*/
	do {

		printf("------------------------------------------------------------------------------\n");
		printf("                            ����������Ϣ����ϵͳ                              \n");
		printf("                                                                              \n");
		printf("           1  ����ά��                                                        \n");
		printf("           2  ���ݲ�ѯ                                                        \n");
		printf("           3  ����ͳ��                                                        \n");
		printf("           4  ���ݵ���/���� (csv�ļ�)                                         \n");
		printf("                                           0  �˳�ϵͳ                        \n");
		printf("------------------------------------------------------------------------------\n");
		printf("��������Ĳ�����");
		op = getch();
		printf("%c\n", op);
		switch (op) {
		case '1':			/*����ά��*/
			char op2, c;
			int num;
			do {
				printf("------------------------------------------------------------------------------\n");
				printf("1 ����������Ϣά��\n");
				printf("2 ����������Ϣά��\n");
				printf("3 �⳵������Ϣά��                0  �˳�ά��\n");
				printf("------------------------------------------------------------------------------\n");
				printf("��������Ĳ�����");
				op2 = getch();
				printf("%c\n", op2);
				switch (op2) {
					/*������Ϣ*/
				case '1':
					char op21;
					do {
						printf("-----------------------------------------------------------------------------\n");
						show_cla(head);
						printf("-----------------------------------------------------------------------------\n");

						printf("����������Ϣ  1 ¼��   2 �޸�  3 ɾ��     0 �˳�������Ϣά��\n");
						printf("��������Ĳ�����");
						op21 = getch();
						printf("%c\n", op21);
						switch (op21) {
						case '1':
							if (in_cla(&head) == OK) printf("¼�����!\n");
							else printf("¼�����!\n");
							break;
						case '2':
							printf("������Ҫ�޸ĵĳ���������룺");
							c = getch();
							printf("%c\n", c);
							if (mod_cla(&head, c) == OK)
								printf("�޸���ɣ�\n");
							else printf("�޸ĳ���!\n");
							break;
						case '3':
							printf("������Ҫɾ���ı�ţ�");
							c = getch();
							printf("%c\n", c);
							if (del_cla(&head, c) == OK)
								printf("ɾ����ɣ�\n");
							else
								printf("�����ڣ�\n");
							break;
						case '0':break;
						}
					} while (op21 != '0');
					break;
					/*������Ϣ*/
				case '2':
					char op22;
					do {
						show_cla(head);
						printf("��������Ҫ�����ĳ����������(��0�˳�)��");
						c = getch();
						printf("%c\n", c);
						if (c == '0')
							break;
						cla_list p = head->cla_next;/*pΪ����������������Ϣ����ͷ���*/
						while (p != NULL && p->car_code != c) {
							p = p->cla_next;
						}
						if (p == NULL || c == '0') {
							printf("û���ҵ���\n");
							continue;
						}
						show_inf(p);
						printf("-----------------------------------------------------------------------------\n");
						printf("����������Ϣ  1 ¼��  2 �޸�  3 ɾ��   0 �˳�������Ϣά��\n");
						printf("��������Ĳ�����");
						op22 = getch();
						printf("%c\n", op22);
						switch (op22) {
						case '1':
							if (in_inf(&p) == OK) printf("¼�����!\n");
							else printf("¼�����!\n");
							break;
						case '2':
							printf("������Ҫ�޸ĵĳ������(0�˳�����)��");
							scanf("%d", &num);
							getchar();
							if (num == 0)  continue;
							if (mod_inf(&p, num) == OK)
								printf("�޸���ɣ�\n");
							else printf("�޸ĳ���!\n");
							break;
						case '3':
							printf("������Ҫɾ���ĳ������(0�˳�����)��");
							scanf("%d", &num);
							getchar();
							if (num == 0) continue;
							if (del_inf(&p, num) == OK)
								printf("ɾ����ɣ�\n");
							else
								printf("�����ڣ�\n");
							break;
						case '0':break;
						}
					} while (op22 != '0');
					break;
					/*������Ϣ*/
				case '3':
					char op23, rt[20];
					int num1;
					do {
						/*��λ��������Ϣ��ͷ���*/
						show_cla(head);
						printf("��������Ҫ�����ĳ����������(��0�˳�)��");
						c = getch();
						printf("%c\n", c);
						if (c == '0')	break;
						/*pΪ����������������Ϣ����ͷ���*/
						cla_list p = head->cla_next;
						while (p != NULL && p->car_code != c) {
							p = p->cla_next;
						}
						if (p == NULL) {
							printf("û���ҵ���\n");
							continue;
						}
						show_inf(p);
						/*��λ���⳵��Ϣ��ͷ�ڵ�*/
						printf("��������Ҫ�����ĳ������(��0�˳�)��");
						scanf("%d", &num1);	getchar();
						if (c == 0) break;
						inf_list p1 = p->inf_next;
						while (p1 != NULL && p1->car_number != num1) {
							p1 = p1->inf_next;
						}
						if (p1 == NULL) { printf("û���ҵ���\n"); continue; }
						show_rent(p1);
						printf("-----------------------------------------------------------------------------\n");
						printf("�⳵������Ϣ  1 ¼��  2 �޸�  3 ɾ��    0 �˳��⳵������Ϣά��\n");
						printf("��������Ĳ�����");
						op23 = getch();
						printf("%c\n", op23);
						switch (op23) {
						case '1':
							if (in_rent(&p1) == OK) printf("¼�����!\n");
							else printf("¼�����!\n");
							break;
						case '2':
							printf("������Ҫ�޸ĵĶ�����ţ�");
							scanf("%s", rt); getchar();
							if (mod_rent(&p1, rt) == OK)
								printf("�޸���ɣ�\n");
							else printf("�޸ĳ���!\n");
							break;
						case '3':
							printf("������Ҫɾ���Ķ�����ţ�");
							scanf("%s", rt); getchar();
							if (del_rent(&p1, rt) == OK)
								printf("ɾ����ɣ�\n");
							else
								printf("�����ڣ�\n");
							break;
						case '0':break;
						}
					} while (op23 != '0');
					break;
				case '0':break;
				}
			} while (op2 != '0');
			break;
		case '2':			/*���ݲ�ѯ*/
			char op3;
			do {
				printf("------------------------------------------------------------------------------\n");
				printf("1 ����������Ϣ��ѯ\n");
				printf("2 ����������Ϣ��ѯ\n");
				printf("3 �⳵������Ϣ��ѯ \n");
				printf("4 ���ɲ�ѯ                0  �˳���ѯ\n");
				printf("------------------------------------------------------------------------------\n");
				printf("��������Ĳ�����");
				op3 = getch();
				printf("%c\n", op3);
				switch (op3) {
				case '1': {
					inf_list h_i = (inf_list)malloc(sizeof(inf_node));//���泵������ĳ�����Ϣ��ѯ���
					h_i->rent_next = NULL;
					cla_list h1 = (cla_list)malloc(sizeof(cla_node));
					cla_list h1_next = (cla_list)malloc(sizeof(cla_node));
					h1->cla_next = h1_next;
					h1->inf_next = NULL;
					h1_next->inf_next = h_i;
					h1_next->cla_next = NULL;
					char temp311[20];
					int flag = 0; //��û���ҵ�����;
					inf_list pt;
					do {
						printf("��������Ҫ��ĳ������ͣ�����*  ��ѯȫ�������޳�����,����0����\n");
						scanf("%s", temp311);
						getchar();
						if (temp311[0] == '0') break;
						else if (temp311[0] == '*') {
							cla_list p = head->cla_next;
							inf_list t;
							while (p != NULL) {
								t = p->inf_next;
								while (t != NULL) {
									if (t->car_status == 'n') {
										memcpy(h_i, t, sizeof(inf_node));
										h_i->inf_next = (inf_list)malloc(sizeof(inf_node));
										h_i->inf_next->rent_next = NULL;
										pt = h_i;
										h_i = h_i->inf_next;
										flag = 1;//�ҵ�
									}
									t = t->inf_next;
								}
								p = p->cla_next;
							}
							break;
						}
						else {
							cla_list p = head->cla_next;
							inf_list t;
							while (p != NULL) {
								if (strcmp(p->car_type, temp311) == 0) {
									t = p->inf_next;
									while (t != NULL) {
										if (t->car_status == 'n') {
											memcpy(h_i, t, sizeof(inf_node));
											h_i->inf_next = (inf_list)malloc(sizeof(inf_node));
											h_i->inf_next->rent_next = NULL;
											pt = h_i;
											h_i = h_i->inf_next;
											flag = 1;
										}
										t = t->inf_next;
									}
								}
								p = p->cla_next;
							}
						}
					} while (temp311[0] != '0');
					if (flag) {
						free(pt->inf_next);
						pt->inf_next = NULL;
						printf("----------------------------------��ѯ���----------------------------------------\n");
						show_inf(h1->cla_next);
						printf("----------------------------------------------------------------------------------\n");
						printf("�Ƿ񵼳����β�ѯ?(y/n): ");
						char out = getch();
						printf("%c\n", out);
						if (out == 'y') {
							printf("�����뵼�����ļ���: ");
							scanf("%s", pathwrite);
							write_to_csv2(&h1, pathwrite);
						}
					}
					else
						printf("----------------------------------û���ҵ����õĳ���------------------------------\n");
				}
						break;
				case '2': {
					inf_list h_i = (inf_list)malloc(sizeof(inf_node));//������Ϣ��ѯ
					h_i->rent_next = NULL;
					cla_list h1 = (cla_list)malloc(sizeof(cla_node));
					cla_list h1_next = (cla_list)malloc(sizeof(cla_node));
					h1->cla_next = h1_next;
					h1->inf_next = NULL;
					h1_next->inf_next = h_i;
					h1_next->cla_next = NULL;
					char temp311[20];
					char temp312[20];
					char temp313[20];
					inf_list pt;
					printf("������Ҫ��ѯ�ĳ��ƺ���(֧��ģ����ѯ)������*����: ");//����
					scanf("%s", temp311);
					if (temp311[0] == '*') {
						cla_list p = head->cla_next;
						while (p != NULL) {
							inf_list p1 = p->inf_next;
							while (p1 != NULL) {
								memcpy(h_i, p1, sizeof(inf_node));
								h_i->inf_next = (inf_list)malloc(sizeof(inf_node));
								h_i->inf_next->rent_next = NULL;
								pt = h_i;
								h_i = h_i->inf_next;
								p1 = p1->inf_next;
							}
							p = p->cla_next;
						}
					}
					else {
						cla_list p = head->cla_next;
						while (p != NULL) {
							inf_list p1 = p->inf_next;
							while (p1 != NULL) {
								int flag = 0;
								for (int i = 0; temp311[i] != '\0'; i++) {
									if (p1->car_license_plate_number[i] != temp311[i]) flag = 1;
								}
								if (!flag) {
									memcpy(h_i, p1, sizeof(inf_node));
									h_i->inf_next = (inf_list)malloc(sizeof(inf_node));
									h_i->inf_next->rent_next = NULL;
									pt = h_i;
									h_i = h_i->inf_next;
								}
								p1 = p1->inf_next;
							}
							p = p->cla_next;
						}
					}
					free(pt->inf_next);
					pt->inf_next = NULL;
					//����������ǶԳ��������޸�
					printf("������Ҫ��ѯ�ĳ�������(֧��ģ����ѯ)������*����: ");//��������
					scanf("%s", temp312);
					if (temp312[0] != '*') {
							inf_list p1 = h1_next->inf_next;
							int flag1 = 1;//��ʾ��ͬ
							for (int j = 0; j <= (strlen(p1->car_name) - strlen(temp312)); j++) {
								flag1 = 1;
								for (int i = 0; temp312[i] != '\0'; i++) {
									if (p1->car_name[i + j] != temp312[i]) flag1 = 0;//��ʾ�в�ͬ
								}
								if (flag1)	break;
							}
							//�����p1��Ϊ������ͷ�ڵ�,���ڵ�һ������������Ϣ���������ԣ������һ���ڵ�p1�Ͳ�����Ҫ����ô��������޸�
							//��������м䲿��
							inf_list p2 = p1->inf_next;
							while (p2 != NULL) {
								int flag = 1;
								for (int j = 0; j <=(strlen(p2->car_name) - strlen(temp312)); j++) {
									flag = 1;
									for (int i = 0; temp312[i] != '\0'&& p1->car_name[i + j] != '\0'; i++) {
										if (p2->car_name[i + j] != temp312[i]) flag = 0;//��ʾ�в�ͬ
									}
									if (flag) break;
								}
								if (!flag) {
									p1->inf_next = p1->inf_next->inf_next;
									free(p2);
									p2 = p1->inf_next;
									continue;
								}
								p1 = p1->inf_next;
								p2 = p2->inf_next;
							}
							if (!flag1) {
								inf_list pt1 = h1_next->inf_next;
								h1_next->inf_next = h1_next->inf_next->inf_next;
								free(pt1);
							}
					}
					printf("������Ҫ��ѯ�ĳ�������״̬��y/n   ����*����: ");//����״̬
					scanf("%s", temp313);
					if (temp313[0] != '*') {
						inf_list p1 = h1_next->inf_next;
						inf_list t = p1;
						int flag1 = 0;
						if (p1->car_status != temp313[0]) flag1 = 1;
						p1 = p1->inf_next;
						while (p1 != NULL) {
							if (p1->car_status != temp313[0]) {
								t->inf_next = p1->inf_next;
								free(p1);
								p1 = t->inf_next;
							}
							else
								t = p1;
								p1 = p1->inf_next;
						}
						if (flag1) {
							p1 = h1_next->inf_next;
							h1_next->inf_next = p1->inf_next;
							free(p1);
						}
					}
					printf("----------------------------------��ѯ���----------------------------------------\n");
					show_inf(h1_next);
					printf("----------------------------------------------------------------------------------\n");
					printf("�Ƿ񵼳����β�ѯ���ļ�  ����������Ϣ��ѯ���.csv ? (y/n):  ");
					char out = getch();
					printf("%c\n", out);
					if (out == 'y') {
						write_to_csv2(&h1, path4);
					}
				}
					break;
				case '3':{//�⳵������Ϣ��ѯ��˼·�������������⳵��������������ͷ�ڵ�
					int flag_exit = 0;
					rent_list r_h=(rent_list)malloc(sizeof(rent_node));//�⳵������Ϣ��ͷ�ڵ�
					rent_list t = r_h;//pr���ƶ�����ָ��
					rent_list pt = NULL ;//t��ǰһ��ָ��
					cla_list p = head->cla_next;//cla����ָ��
					inf_list pi = NULL;//infָ��
					rent_list pr = NULL;//rentָ��
					char op33;
					printf("------------------------------------------------------------------------------------\n");
					printf("1  ������Ϣ     2    ������Ϣ     3   �⳵ʱ�䷶Χ                \n");
					printf("������Ҫ���ҵ�����ѡ��: ");
					op33 = getch();
					printf("%c\n", op33);
					if (op33 == '1') {
						char op331;
						printf("1  ���֤��        2 �ֻ���                          0 �˳�            \n");
						printf("������Ҫ��ѯ��ѡ�");
						op331 = getch();
						printf("%c\n", op331);
						if (op331 == '1') {
							char t_id[20];
							printf("���������֤�ţ�");
							scanf("%s", t_id);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									while (pr != NULL) {
										if (strcmp(pr->person_id, t_id) == 0) {//�ҵ�һ�����ʶ���
											*t = *pr;
											t->rent_next = (rent_list)malloc(sizeof(rent_node));
											pt = t;
											t = t->rent_next;
											flag_exit = 1;
										}
										pr = pr->rent_next;
									}
									pi = pi->inf_next;
								}
								p = p->cla_next;
							}
						}
						else if (op331 == '2') {
							char t_phone[20];
							printf("�������ֻ����룺");
							scanf("%s", t_phone);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									while (pr != NULL) {
										if (strcmp(pr->person_phone, t_phone) == 0) {//�ҵ�һ�����ʶ���
											*t = *pr;
											t->rent_next = (rent_list)malloc(sizeof(rent_node));
											pt = t;
											t = t->rent_next;
											flag_exit = 1;
										}
										pr = pr->rent_next;
									}
									pi = pi->inf_next;
								}
								p = p->cla_next;
							}
						}
					}
					else if (op33 == '2') {
						char op332;
						printf("1  ���ƺ���        2 ��������                                       \n");
						printf("������Ҫ��ѯ��ѡ�");
						op332 = getch();
						printf("%c\n", op332);
						if (op332 == '1') {
							char t_license[20];
							printf("�����복�ƺ��룺");
							scanf("%s", t_license);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									if ( strcmp( pi->car_license_plate_number , t_license ) == 0 ) {//�ҵ����ʵĳ���
										while (pr != NULL) {
											*t = *pr;
											t->rent_next = (rent_list)malloc(sizeof(rent_node));
											pt = t;
											t = t->rent_next;
											pr = pr->rent_next;
											flag_exit = 1;
										}

									}
									pi = pi->inf_next;
								}
								p = p->cla_next;
							}
						}
						if (op332 == '2') {
							char t_name[20];
							printf("�����복�����ƣ�");
							scanf("%s", t_name);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									if (strcmp(pi->car_name, t_name) == 0) {//�ҵ����ʵĳ���
										while (pr != NULL) {
											*t = *pr;
											t->rent_next = (rent_list)malloc(sizeof(rent_node));
											pt = t;
											t = t->rent_next;
											pr = pr->rent_next;
											flag_exit = 1;
										}
									}
									pi = pi->inf_next;
								}
								p = p->cla_next;
							}
						}
					}
					else if (op33 == '3') {
						char t_start[20];
						char t_end[20];
						printf("�ӣ�����20190224����");
						scanf("%s", t_start);
						t_start[8] = '0';
						t_start[9] = '0';
						t_start[10] = '\0';
						printf("��������20190512����");
						scanf("%s", t_end);
						t_end[8] = '9';
						t_end[9] = '9';
						t_end[10] = '\0';
						while (p != NULL) {
						pi = p->inf_next;
						while (pi != NULL) {
							pr = pi->rent_next;
							while (pr != NULL) {
								if (atoi(pr->rent_number)>=atoi(t_start)&& atoi(pr->rent_number) <= atoi(t_end)){//�ҵ�һ�����ʶ���
									*t = *pr;
									t->rent_next = (rent_list)malloc(sizeof(rent_node));
									pt = t;
									t = t->rent_next;
									flag_exit = 1;
								}
								pr = pr->rent_next;
							}
							pi = pi->inf_next;
						}
						p = p->cla_next;
					}
					}
					if (flag_exit) {
						free(pt->rent_next);
						pt->rent_next = NULL;
						inf_list h3 = (inf_list)malloc(sizeof(inf_node));
						h3->inf_next = NULL;
						h3->rent_next = r_h;
						cla_list h1 = (cla_list)malloc(sizeof(cla_node));
						cla_list h1_next = (cla_list)malloc(sizeof(cla_node));
						h1->cla_next = h1_next;
						h1->inf_next = NULL;
						h1_next->cla_next = NULL;
						h1_next->inf_next = h3;
						printf("----------------------------------��ѯ���----------------------------------------\n");
						show_rent(h3);
						printf("----------------------------------------------------------------------------------\n");
						printf("�Ƿ񵼳����β�ѯ��  �⳵������Ϣ��ѯ���.csv��  (y/n): ");
						char out = getch();
						printf("%c\n", out);
						if (out == 'y') {
							//						printf("�����뵼�����ļ���: ");
							//						scanf("%s", pathwrite);
							write_to_csv3(&h1, path5);
						}
					}
					else
						printf("--------------------------------�����ڸö���--------------------------------------\n");
				}
					break;
				case'4': {
					int flag_exit = 0;	
					rent_list h = (rent_list)malloc(sizeof(rent_node));//�⳵������Ϣ��ͷ�ڵ�
					rent_list r_h = (rent_list)malloc(sizeof(rent_node));//�⳵������Ϣ�ĵ�һ����
					h->rent_next = r_h;
					rent_list t = r_h;//pr���ƶ�����ָ��
					rent_list pt = NULL;//t��ǰһ��ָ��
					cla_list p = head->cla_next;//cla����ָ��
					inf_list pi = NULL;//inf����ָ��
					rent_list pr = NULL;//rent����ָ��
					while (p != NULL) {
						pi = p->inf_next;
						while (pi != NULL) {
							pr = pi->rent_next;
							while (pr != NULL) {
								*t = *pr;
								t->rent_next = (rent_list)malloc(sizeof(rent_node));
								pt = t;
								t = t->rent_next;
								flag_exit = 1;
								pr = pr->rent_next;
							}
							pi = pi->inf_next;
						}
						p = p->cla_next;
					}
					if (flag_exit == 0) {
						free(r_h);
						printf("-----------------------û�ж���-------------------------\n");
					}
					else {
						free(pt->rent_next);
						pt->rent_next = NULL;
						char t_date[20];
						char a[20];
						char b[20];
						printf("����������(*����):  ");
						scanf("%s", t_date);
						if (t_date[0] != '*') {
							strcpy(a, t_date);
							strcpy(b, t_date);
							a[8] = '0'; a[9] = '0'; a[10] = '\0';
							b[8] = '9'; b[9] = '9'; b[10] = '\0';
							t = h;
							while (t->rent_next != NULL) {
								if (atoi(t->rent_next->rent_number) < atoi(a) || atoi(t->rent_next->rent_number) > atoi(b)) {//���ڷ�Χ��
									pt = t->rent_next;
									t->rent_next = t->rent_next->rent_next;
									free(pt);
								}
								else t = t->rent_next;
							}
						}
						char t_type[20];
						printf("�����복������(*����)��");
						scanf("%s",t_type);
						if (t_type[0] != '*') {
							p = head->cla_next;
							while (p!=NULL&&strcmp(p->car_type, t_type) != 0) {
								p = p->cla_next;
							}
							if (p != NULL) {
								int f1=0;//��������кͶ���һ���ı�ų�����־
								t = h;
								while (t->rent_next != NULL) {
									pi = p->inf_next;
									while (pi != NULL) {
										if (pi->car_number == t->rent_next->car_number) f1 = 1;//�о�t����ת�Ƶ���һ����㣬û�о�ɾ��������t->rent_next
										pi = pi->inf_next;
									}
									if (f1 == 0) {
										pt = t->rent_next;
										t->rent_next = t->rent_next->rent_next;
										free(pt);
									}
									else t = t->rent_next;
								}

							}

						}
						char t_name[20];
						printf("�����복������(*����)��");
						scanf("%s", t_name);
						char t_pname[20];
						printf("�������û�����(*����)��");
						scanf("%s", t_pname);
						char t_phone[20];
						printf("�������û��ֻ���(*����)��");
						scanf("%s", t_phone);
						char t_id[20];
						printf("�������û����֤��(*����)��");
						scanf("%s", t_id);
						if (h->rent_next == NULL) {
							printf("------------------------------û�ҵ�����-----------------------------------\n");
							break;
						}
						else {
							cla_list c_h = (cla_list)malloc(sizeof(cla_node));
							cla_list c_next = (cla_list)malloc(sizeof(cla_node));
							inf_list i_h = (inf_list)malloc(sizeof(inf_node));
							c_h->cla_next = c_next;
							c_h->inf_next = NULL;
							c_next->cla_next = NULL;
							c_next->inf_next = i_h;
							i_h->inf_next = NULL;
							i_h->rent_next = h->rent_next;
							printf("----------------------------------��ѯ���----------------------------------------\n");
							show_rent(i_h);
							printf("----------------------------------------------------------------------------------\n");
							printf("�Ƿ񵼳������Զ����ѯ��  (y/n): ");
							char out = getch();
							printf("%c\n", out);
							if (out == 'y') {
								printf("�����뵼�����ļ���: ");
								scanf("%s", pathwrite);
								write_to_csv3(&c_h, pathwrite);
							}
						}
					}
				}
					break;
				case '0':
					break;
				}
			} while (op3 != '0');
			break;
		case '3':				/*����ͳ��*/
			char op4;
			do {
				printf("---------------------------------------------------------------------------------------\n");
				printf("ͳ��ѡ�\n");
				printf("    1  ��ǰ��ǰÿ�ֳ������͵ĳ����������ѳ�������δ������\n");
				printf("    2  ͳ��ÿ��ÿ�ֳ������͵�Ӫҵ�������ʵ�ɷ��ã����������ÿ�ֳ������͵�Ӫҵ����״ͳ��ͼ\n");
				printf("    3  ������ݣ�ͳ�Ƹ���ÿ������Ӫҵ�������ʵ�ɷ��ã���������\n");
				printf("    4  �г��������ۼƳ�����������10�����ĳ�����Ϣ�����ۼƳ���������������������\n   �����֤�š��������ۼ��ⷿ������Ӧ��ס�޷��ܶʵ��ס�޷��ܶ�\n");
				printf("    0  �˳�\n");
				printf("---------------------------------------------------------------------------------------\n");
				printf("������Ҫѡ���ͳ�ƣ�");
				op4 = getch();
				printf("%c\n", op4);
				switch (op4) {
				case '1':{
					int i=0;
					int num[5] = { 0 };
					int num_y[5] = { 0 };
					cla_list p = head->cla_next;
					inf_list t = NULL;
					for (i = 0; p != NULL && i<=4;i++) {
						t = p->inf_next;
						while (t != NULL) {
							num[i]++;
							if (t->car_status == 'y')
								num_y[i]++;
							t = t->inf_next;
						}
						p = p->cla_next;
					}
					printf("---------------------------------------ͳ�ƽ��---------------------------------------\n");
					printf("  ��������              ��������                �ѳ�����                δ������          \n");
					printf("  ������                  %2d                      %2d                    %2d                 \n", num[0], num_y[0], num[0] - num_y[0]);
					printf("  ������                  %2d                      %2d                    %2d                 \n", num[1], num_y[1], num[1] - num_y[1]);
					printf("  ������                  %2d                      %2d                    %2d                 \n", num[2], num_y[2], num[2] - num_y[2]);
					printf("  SUV                     %2d                      %2d                    %2d                 \n", num[3], num_y[3], num[3] - num_y[3]);
					printf("  7�������ϳ���           %2d                      %2d                    %2d                 \n", num[4], num_y[4], num[4] - num_y[4]);
					printf("----------------------------------------------------------------------------------------\n");
					}
					break;
				case '2': {
					int i1;
					float w[5] = { 0 };
					cla_list p = head->cla_next;
					inf_list t = NULL;
					rent_list r = NULL;
					for (i1 = 0; p != NULL && i1 <= 4; i1++) {
						t = p->inf_next;
						while (t != NULL) {
							r = t->rent_next;
							while (r != NULL) {
								w[i1] += r->fee_total_actually;
								r = r->rent_next;
							}
							t = t->inf_next;
						}
						p = p->cla_next;
					}
					printf("---------------------------------------ͳ�ƽ��---------------------------------------\n");
					printf("  ��������                       Ӫҵ��                                                      \n");
					printf("  ������                   %10.2f                                                        \n", w[0]);
					printf("  ������                   %10.2f                                                        \n", w[1]);
					printf("  ������                   %10.2f                                                        \n", w[2]);
					printf("  SUV                      %10.2f                                                        \n", w[3]);
					printf("  7�������ϳ���            %10.2f                                                        \n", w[4]);
					printf("--------------------------------------------------------------------------------------\n");
					printf("�Ƿ����ͼ��(y/n):");
					char t_1;
					t_1 = getch();
					printf("%c\n������˳�ͼ��\n", t_1);
					if(t_1=='y') {
						int i, j;
						initgraph(640, 480, SHOWCONSOLE); // ����һ���� 640 x �� 480 ���صĴ���
						for (i = 0; i < 640; i++) {
							for (j = 0; j < 480; j++)
								putpixel(i, j, RGB(255, 255, 255));
						}
						for (i = 100, j = 100; j <= 400; j++) {
							putpixel(i, j, RGB(0, 0, 0));
							putpixel(i + 1, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 100; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 150; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 200; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 250; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 300; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 350; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
						}
						for (i = 100, j = 400; i <= 540; i++) {
							putpixel(i, j, RGB(0, 0, 0));
							putpixel(i, j + 1, RGB(0, 0, 0));
						}
						setbkmode(TRANSPARENT);
						// 1.�������ֱ���ģʽΪ TRANSPARENT ʵ����������ޱ���ɫ
						settextcolor(RGB(0, 0, 0));
						// 2.����������ɫΪ ��ɫ
						settextstyle(15, 0, _T("����"));
						// 3.�������ִ�С�����壬��������Ϊ���ߡ������塣�����Ϊ 0 ��ʾ����Ӧ,
						// ����_T(��*�� )��*�������滻������ʹ�ó��������壬�磺���塢���塢�����
						outtextxy(50, 95, _T("6000"));
						outtextxy(50, 145, _T("5000"));
						outtextxy(50, 195, _T("4000"));
						outtextxy(50, 245, _T("3000"));
						outtextxy(50, 295, _T("2000"));
						outtextxy(50, 345, _T("1000"));
						outtextxy(50, 395, _T("0"));
						outtextxy(120, 410, _T("������"));
						outtextxy(200, 410, _T("������"));
						outtextxy(280, 410, _T("������"));
						outtextxy(360, 410, _T("SUV"));
						outtextxy(440, 410, _T("7�������ϳ���"));
						for (int i2 = 0; i2 < 5; i2++) {
							setfillstyle(BS_SOLID);
							// 1.���õ�ǰ�����ʽΪ��ʵ
							setfillcolor(RGB(0, 0, 0));
							// 2.���õ�ǰ�����ɫΪ��ɫ
							int a1 = w[i2] / 20;
							wchar_t temp[100];
							_stprintf_s(temp, _T("%.1f"), w[i2]);
							outtextxy(120 + i2 * 80, 400 - a1 - 20, temp);
							solidrectangle(120 + i2 * 80, 400 - a1, 120 + i2 * 80+40, 400);
							// 3.����������������, ���Ͻ����꣨10,20�������½����꣨100,120��
							// 4.�����������������,������(20,30)����� Hello World!չʾ����ַ���������
						}
						getchar(); // ��ͣ�������У��鿴������
						closegraph();// �ر�ͼ�ν���
					}
				}
					break;
				case '3': {
					int i;
					char s_year[20];
					printf("��������ݣ�");
					scanf("%s", s_year);
					char before[20];//year000000
					char after[20];//year999999���������ƶ���֮�伴��
					for (int i = 0; i < 4; i++) {
						before[i] = s_year[i];
						after[i] = s_year[i];
					}
					for (int i = 0; i < 6; i++) {
						before[i+4] = '0';
						after[i+4] ='2';
					}
					before[10] = '\0'; after[10] = '\0';
					cla_list p = head->cla_next;
					inf_list t = NULL;
					rent_list r = NULL;
					float sale,saleall=0;
					float ratetime;
					printf("----------------------------------%s��-----------------------------------\n",s_year);
					printf("  ���ƺ�         ��������                   Ӫҵ��            ������       \n");
					while(p != NULL) {
						t = p->inf_next;
						while (t != NULL) {
							sale = 0; ratetime = 0;
							r = t->rent_next;
							while (r != NULL && atoi(r->rent_number) >= atoi(before) && atoi(r->rent_number) <= atoi(after)) {
								sale += r->fee_total_actually;
								r = r->rent_next;
								ratetime+=1;
							}
							printf("  %s       %-15s            %6.2f          %.6f  \n",
								t->car_license_plate_number, t->car_name, sale, ratetime / 365);
							saleall += sale;
							t = t->inf_next;
						}
						p = p->cla_next;
					}
					printf("                           Ӫҵ�ܶ�: %f                  \n",saleall);
					printf("--------------------------------------------------------------------------------\n");
				}
					break;
				case '4': {//��˳���¼ÿ���ڵ������ʱ�䣬ͬʱ����һ��������Ϣ������������ͳ�������������ð�����򣬵õ���������
					int i=0;
					int day[50] = { 0 };
					char a[4] = { 0 };
					char b[4] = { 0 };
					inf_list car_list = (inf_list)malloc(sizeof(inf_node));
					car_list->rent_next = NULL;
					inf_list t = car_list;
					inf_list pt = car_list;

					cla_list p = head->cla_next;
					inf_list it = NULL;
					rent_list rt = NULL;
					while (p != NULL) {
						it = p->inf_next;
						while (it != NULL) {
							*t = *it;//��������
							t->inf_next = (inf_list)malloc(sizeof(inf_node));
							t->inf_next->rent_next = NULL;
							pt = t;
							t = t->inf_next;

							rt = it->rent_next;
							while (rt != NULL) {
								a[0] = rt->date_take[8];
								a[1] = rt->date_take[9];
								a[2] = '\0';
								b[0] = rt->date_return_actually[8];
								b[1] = rt->date_return_actually[9];
								b[2] = '\0';
								day[i] += (atoi(b) - atoi(a));
								rt = rt->rent_next;
							}
							i++;
							it = it->inf_next;
						}
						p = p->cla_next;
					}
					free(pt->inf_next);
					pt->inf_next = NULL;//���������������
					//day[0]����һ����ʱ�䣬�Դ�����
					//������ð�������㷨
					int flag;
					inf_list ch = (inf_list)malloc(sizeof(inf_node));
					ch->inf_next = car_list;
					ch->rent_next = NULL;
					do {
						i = 0;flag = 0;
						inf_list p1 = ch;
						inf_list p2 = ch->inf_next;
						while (p2->inf_next != NULL) {//p2�ǵ�һ����㣬p1��ͷ�ڵ�
							if (day[i] < day[i + 1]) {
								flag = 1;//��ʾû���꣬���ڲ���
								p1->inf_next = p1->inf_next->inf_next;//�������
								p2->inf_next = p2->inf_next->inf_next;
								p1->inf_next->inf_next = p2;
								int temp = day[i];//��������ʱ��
								day[i] = day[i + 1];
								day[i + 1] = temp;
							}
							p1 = p1->inf_next;
							p2 = p2->inf_next;
							i++;
						}

					} while (flag == 1);
					printf("---------------------------------------------------------------------------------------------\n");
					printf("���ƺ�                    ��������            �ۼƳ�������         Ӫҵ��          ������     \n");
					inf_list t1 = ch->inf_next;
					for (i = 0; i < 10&& t1!=NULL ; i++) {
						printf("%s          %15s                %2d                %6f         %6f \n",
							t1->car_license_plate_number,t1->car_name,day[i],day[i]*t1->fee_daily,float(day[i])/365);
						t1 = t1->inf_next;
					}
					printf("---------------------------------------------------------------------------------------------\n");
					
				}
					break;
				case '0':
					break;
				}
			} while (op4 != '0');
			break;
		case '4':			/*���ݵ��뵼��*/
			char op1;
			do {
				printf("1  ���ݵ���             2  ���ݵ���          0  �˳� \n");
				op1 = getch();
				printf("%c\n", op1);
				switch (op1) {
				case '1':
					if (get_from_csv1(&head, path1) == OK && get_from_csv2(&head, path2) == OK && get_from_csv3(&head, path3) == OK) {
						printf("-----------------------------������-----------------------------------\n");
					}
					else {
						printf("�����ļ�Ϊ��\n");
					}
					break;

				case '2':
					if (write_to_csv1(&head, path1) == OK && write_to_csv2(&head, path2) == OK && write_to_csv3(&head, path3) == OK) {}
					else {
						printf("�����ļ�ʧ�ܣ������µ���\n");
						return ERROR;
					}
					break;
				}
			} while (op1 != '0');
			break;
		case '0':
			printf("--------------------------- ��лʹ�ã�----------------------------------- \n");
			break;
		}
	}while (op != '0');

	/*�Զ�����*/
	if (write_to_csv1(&head, path01) == OK && write_to_csv2(&head, path02) == OK && write_to_csv3(&head, path03) == OK) {
		printf("------------------------------------------------------------------------------\n");
		printf("-----------------------------����dat�����ѱ���--------------------------------\n");
	}

	free_cla(&head);
	return 0;
}