#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<graphics.h>   //easyx图形
#include<easyx.h>   //easyx图形

#define PATH1 "车辆分类信息表.csv"
#define PATH2 "车辆基本信息表.csv"
#define PATH3 "租车订单信息表.csv"
#define PATH4 "车辆基本信息查询结果.csv"
#define PATH5 "租车订单信息查询结果.csv"
#define PATH01 "车辆分类信息表.dat"
#define PATH02 "车辆基本信息表.dat"
#define PATH03 "租车订单信息表.dat"
#define TURE 1
#define OK 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -1
typedef int status;  //状态返回值

/*车辆分类信息表*/
struct cla_node {
public:
	char car_code;  //车辆类型编码
	char car_type[20];
	int car_remain;
	struct cla_node* cla_next;
	struct inf_node* inf_next;
}cla_node, * cla_list;

/*车辆基本信息表*/
struct inf_node {
public:
	int car_number;  //车辆编号
	char car_license_plate_number[10];
	char car_code;
	char car_name[20];
	char gear_way[10];
	float fee_daily;
	char car_status;
	struct inf_node* inf_next;
	struct rent_node* rent_next;

}inf_node, * inf_list;

/*租车订单信息表*/
struct rent_node {
public:
	char rent_number[20];
	char person_id[20];
	char person_name[20];
	char person_phone[20];
	int car_number;	
	char date_take[18];
	char date_return_schedule[18];
	float deposit;//押金 =所租费用*5
	char date_return_actually[18];
	float fee_total_schedule;
	float fee_total_actually;
	struct rent_node* rent_next;
}rent_node, * rent_list;

/*文件载入*/
//载入车辆分类信息 head为头结点指针 path为路径
status get_from_csv1(cla_list* head, char* path) {
	cla_list p = *head;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("未能打开文件\n");
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
		memset(tmp_buf, 0, sizeof(tmp_buf));/*清空temp_buf*/
	}
	fclose(fp);
	return OK;
}

//载入车辆基本信息表 head为头结点指针 path为路径
status get_from_csv2(cla_list* head, char* path) {//载入车辆基本信息表
	cla_list p = (*head)->cla_next;
	inf_list p_inf = (inf_list)malloc(sizeof(inf_node));;
	inf_list t = NULL;
	p->inf_next = p_inf;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("未能打开文件\n");
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
		if ( temp2[0] != p->car_code ) {//下一类车辆快来！
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
		memset(tmp_buf, 0, sizeof(tmp_buf));/*清空temp_buf*/
	}
	free(t->inf_next);
	t->inf_next = NULL;
	fclose(fp);
	return OK;
}

//载入租车订单信息表 head为头结点指针 path为路径
status get_from_csv3(cla_list* head, char* path) {//载入租车订单信息表
	cla_list p = (*head)->cla_next;
	inf_list p_inf = p->inf_next;
	char tmp_buf[1024] = { 0 };
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		printf("未能打开文件\n");
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
			 if (p_inf == NULL) {  //切换下一类车
				 p = p->cla_next;
				 p_inf = p->inf_next;
				 continue;
			 }
			 if (p_inf->car_number == atoi(temp4)) break;  //找到对应编号车辆
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
		 memset(tmp_buf, 0, sizeof(tmp_buf));/*清空temp_buf*/
	}
	fclose(fp);
	return OK;
}

/*导出到文件*/
//导出到车辆分类信息表.csv     head为头结点指针 path为路径
status write_to_csv1(cla_list* head, char* path){
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w+");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "车辆类型编码,车辆类型名称,库存数量\n");
	while (p != NULL) {
		fprintf(f, "%c,%s,%d\n", p->car_code, p->car_type, p->car_remain);
		p = p->cla_next;
	}
	printf("-----------------------------已导出到%s----------------------------\n", path);
	fclose(f);
	return OK;
}
//导出到车辆基本信息表.csv      head为头结点指针 path为路径
status write_to_csv2(cla_list* head, char* path){
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "车辆编号,车牌号,车辆类型编码,车辆名称,排挡方式,每日租金（元）,出租状态\n");
	while (p != NULL) {
		inf_list p_inf = p->inf_next;
		while (p_inf != NULL) {
			fprintf(f, "%d,%s,%c,%s,%s,%f,%c\n", p_inf->car_number, p_inf->car_license_plate_number, p_inf->car_code, p_inf->car_name, p_inf->gear_way, p_inf->fee_daily, p_inf->car_status);
			p_inf = p_inf->inf_next;
		}
		p = p->cla_next;
	}
	printf("-----------------------------已导出到%s----------------------------\n", path);
	fclose(f);
	return OK;
}

//导出到租车订单信息表.csv    head为头结点指针 path为路径
status write_to_csv3(cla_list* head, char* path) {
	cla_list p = (*head)->cla_next;
	FILE* f = fopen(path, "w");
	if (f == NULL) {
		return ERROR;
	}
	fprintf(f, "订单编号,身份证号,客人姓名,手机号码,租用车辆编号,取车时间,预约还车时间,押金（元）,实际还车时间,应缴费用（元）,实缴费用（元）\n");
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
	printf("-----------------------------已导出到%s----------------------------\n", path);
	fclose(f);
	return OK;
}

/*创建车辆分类结点*/
status in_cla(cla_list* head) {
	cla_list h = *head;
	while (h->cla_next != NULL) {
		h = h->cla_next;
	}
	h->cla_next = (cla_list)malloc(sizeof(cla_node));
	h = h->cla_next;
	printf("依次输入\n车辆编号(数字)，类型(如经济性)，库存数量(数量)  空格隔开\n");
	scanf("%c %s %d", &h->car_code, h->car_type, &h->car_remain);
	getchar();
	h->cla_next = NULL;
	h->inf_next = NULL;
	return OK;
}

/*修改车辆分类*/
status mod_cla(cla_list* head, char c) {
	cla_list p = (*head)->cla_next;
	while (p != NULL && p->car_code != c) {
		p = p->cla_next;
	}
	if (p != NULL) {
		//	memset(p->car_type, 0, sizeof(p->car_type));		//清空字符数组（多余！）
		printf("请全部重新修改(车辆编号，类型，库存数量)：");
		scanf("%c %s %d", &p->car_code, p->car_type, &p->car_remain);
		getchar();
	}
	else {
		printf("没有找到\n");
		return ERROR;
	}
	return OK;
}

/*删除车辆分类并释放空间*/
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

/*显示目前的车辆分类信息*/
void show_cla(cla_list h) {
	cla_list p = h->cla_next;
	printf("---------------------------------车辆分类信息----------------------------------\n");
	printf("车辆编号            类型                库存\n");
	while (p != NULL) {
		printf("%-20c%-20s%-20d\n", p->car_code, p->car_type, p->car_remain);
		p = p->cla_next;
	}
}

/*创建车辆基本信息结点*/
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
	printf("依次输入车辆的  编号，车牌号，车辆名称，排挡方式，每日租金，出租状态（y/n)  空格隔开\n");
	scanf("%d %s %s %s %f %c", &t->car_number, t->car_license_plate_number, t->car_name, t->gear_way, &t->fee_daily, &t->car_status);
	getchar();
	t->car_code = (*head)->car_code;
	t->inf_next = NULL;
	t->rent_next = NULL;
	return OK;
}

/*修改车辆基本信息*/
status mod_inf(cla_list* head, int num) {
	inf_list p = (*head)->inf_next;
	while (p != NULL && p->car_number != num) {
		p = p->inf_next;
	}
	if (p != NULL) {
		printf("请重新输入该车辆基本信息：");
		printf("依次输入车辆的  编号，车牌号，车辆名称，排挡方式，每日租金，出租状态（y/n)\n");
		scanf("%d %s %s %s %f %c", &p->car_number, p->car_license_plate_number, p->car_name, p->gear_way, &p->fee_daily, &p->car_status);
		getchar();
	}
	else {
		printf("没有该编号车辆!\n");
		return ERROR;
	}
	return OK;
}

/*删除车辆基本信息并释放空间*/
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

/*显示目前车辆基本信息*/
void show_inf(cla_list h) {
	inf_list t = h->inf_next;
	printf("当前所有车辆如下：\n"); printf("编号 车牌号                车辆类型编码     车辆名称            排挡方式           每日租金   出租状态（y/n):\n");
	while (t != NULL) {
		printf("%-5d %-20s %-15c %-20s %-20s %-10.1f %-c\n", t->car_number, t->car_license_plate_number, t->car_code, t->car_name, t->gear_way, t->fee_daily, t->car_status);
		t = t->inf_next;
	}
}

/*创建租车订单信息结点*/
status in_rent(inf_list* head) {
	int d_sch, d_real;
	rent_list p = (*head)->rent_next;
	rent_list t = (rent_list)malloc(sizeof(rent_node));
	if (p == NULL) { (*head)->rent_next = t; }
	else {
		while (p->rent_next != NULL) p = p->rent_next;
		p->rent_next = t;
	}
	printf("依次输入订单编号，客人姓名，身份证号，手机号码，取车时间，预约还车时间，实际还车时间（0表示未归还） 空格隔开\n");
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

/*修改租车订单信息*/
status mod_rent(inf_list* head, char rt[]) {
	rent_list t = (*head)->rent_next;
	while (t != NULL && strcmp(t->rent_number, rt) != 0) { t = t->rent_next; }
	if (t != NULL) {
		printf("请重新输入订单信息\n");
		printf("依次输入订单编号，客人姓名，身份证号，手机号码，取车时间，预约还车时间，实际还车时间（0表示未归还）\n");
		scanf("%s %s %s %s %s %s %s", t->rent_number, t->person_name, t->person_id, t->person_phone,
			t->date_take, t->date_return_schedule, t->date_return_actually);
	}
	else {
		printf("没有该租车订单！\n");
		return ERROR;
	}
	return OK;
}

/*删除租车订单信息并释放空间*/
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

/*显示目前车辆租车订单信息*/
void show_rent(inf_list h) {
	rent_list p = h->rent_next;
	printf("当前车辆的所有订单如下：\n");
	printf("订单编号    身份证号         客人姓名     手机号码       租用车辆编号      取车时间        预约还车时间       押金     实际还车时间     应缴费用    实缴费用\n");
	while (p != NULL) {
		printf("%-10s%-20s%-10s%-20s%-10d%-20s%-20s%-10.1f%-20s%-10.1f%-10.1f\n", p->rent_number, p->person_id, p->person_name, p->person_phone, p->car_number, p->date_take,
			p->date_return_schedule, p->deposit, p->date_return_actually, p->fee_total_schedule, p->fee_total_actually);
		p = p->rent_next;
	}
}

/*释放内存空间*/
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

/*主函数*/
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
		printf("初始化表头出错！\n");
		return 0;
	}
	head->cla_next = NULL;
	head->inf_next = NULL;

	/*自动载入*/
	if (get_from_csv1(&head, path01) == OK && get_from_csv2(&head, path02) == OK && get_from_csv3(&head, path03)) {
		printf("------------------------------------------------------------------------------\n");
		printf("-----------------------------上次dat数据已载入--------------------------------\n");
	}
	else {
		printf("载入文件失败，请检查文件\n");
		return ERROR;
	}

	/*主菜单*/
	do {

		printf("------------------------------------------------------------------------------\n");
		printf("                            汽车租赁信息管理系统                              \n");
		printf("                                                                              \n");
		printf("           1  数据维护                                                        \n");
		printf("           2  数据查询                                                        \n");
		printf("           3  数据统计                                                        \n");
		printf("           4  数据导入/导出 (csv文件)                                         \n");
		printf("                                           0  退出系统                        \n");
		printf("------------------------------------------------------------------------------\n");
		printf("请输入你的操作：");
		op = getch();
		printf("%c\n", op);
		switch (op) {
		case '1':			/*数据维护*/
			char op2, c;
			int num;
			do {
				printf("------------------------------------------------------------------------------\n");
				printf("1 车辆分类信息维护\n");
				printf("2 车辆基本信息维护\n");
				printf("3 租车订单信息维护                0  退出维护\n");
				printf("------------------------------------------------------------------------------\n");
				printf("请输入你的操作：");
				op2 = getch();
				printf("%c\n", op2);
				switch (op2) {
					/*分类信息*/
				case '1':
					char op21;
					do {
						printf("-----------------------------------------------------------------------------\n");
						show_cla(head);
						printf("-----------------------------------------------------------------------------\n");

						printf("车辆分类信息  1 录入   2 修改  3 删除     0 退出分类信息维护\n");
						printf("请输入你的操作：");
						op21 = getch();
						printf("%c\n", op21);
						switch (op21) {
						case '1':
							if (in_cla(&head) == OK) printf("录入完成!\n");
							else printf("录入出错!\n");
							break;
						case '2':
							printf("请输入要修改的车辆分类编码：");
							c = getch();
							printf("%c\n", c);
							if (mod_cla(&head, c) == OK)
								printf("修改完成！\n");
							else printf("修改出错!\n");
							break;
						case '3':
							printf("请输入要删除的编号：");
							c = getch();
							printf("%c\n", c);
							if (del_cla(&head, c) == OK)
								printf("删除完成！\n");
							else
								printf("不存在！\n");
							break;
						case '0':break;
						}
					} while (op21 != '0');
					break;
					/*基本信息*/
				case '2':
					char op22;
					do {
						show_cla(head);
						printf("请输入你要操作的车辆分类编码(按0退出)：");
						c = getch();
						printf("%c\n", c);
						if (c == '0')
							break;
						cla_list p = head->cla_next;/*p为待操作车辆基本信息链的头结点*/
						while (p != NULL && p->car_code != c) {
							p = p->cla_next;
						}
						if (p == NULL || c == '0') {
							printf("没有找到！\n");
							continue;
						}
						show_inf(p);
						printf("-----------------------------------------------------------------------------\n");
						printf("车辆基本信息  1 录入  2 修改  3 删除   0 退出基本信息维护\n");
						printf("请输入你的操作：");
						op22 = getch();
						printf("%c\n", op22);
						switch (op22) {
						case '1':
							if (in_inf(&p) == OK) printf("录入完成!\n");
							else printf("录入出错!\n");
							break;
						case '2':
							printf("请输入要修改的车辆编号(0退出操作)：");
							scanf("%d", &num);
							getchar();
							if (num == 0)  continue;
							if (mod_inf(&p, num) == OK)
								printf("修改完成！\n");
							else printf("修改出错!\n");
							break;
						case '3':
							printf("请输入要删除的车辆编号(0退出操作)：");
							scanf("%d", &num);
							getchar();
							if (num == 0) continue;
							if (del_inf(&p, num) == OK)
								printf("删除完成！\n");
							else
								printf("不存在！\n");
							break;
						case '0':break;
						}
					} while (op22 != '0');
					break;
					/*订单信息*/
				case '3':
					char op23, rt[20];
					int num1;
					do {
						/*定位到基本信息的头结点*/
						show_cla(head);
						printf("请输入你要操作的车辆分类编码(按0退出)：");
						c = getch();
						printf("%c\n", c);
						if (c == '0')	break;
						/*p为待操作车辆基本信息链的头结点*/
						cla_list p = head->cla_next;
						while (p != NULL && p->car_code != c) {
							p = p->cla_next;
						}
						if (p == NULL) {
							printf("没有找到！\n");
							continue;
						}
						show_inf(p);
						/*定位到租车信息的头节点*/
						printf("请输入你要操作的车辆编号(按0退出)：");
						scanf("%d", &num1);	getchar();
						if (c == 0) break;
						inf_list p1 = p->inf_next;
						while (p1 != NULL && p1->car_number != num1) {
							p1 = p1->inf_next;
						}
						if (p1 == NULL) { printf("没有找到！\n"); continue; }
						show_rent(p1);
						printf("-----------------------------------------------------------------------------\n");
						printf("租车订单信息  1 录入  2 修改  3 删除    0 退出租车订单信息维护\n");
						printf("请输入你的操作：");
						op23 = getch();
						printf("%c\n", op23);
						switch (op23) {
						case '1':
							if (in_rent(&p1) == OK) printf("录入完成!\n");
							else printf("录入出错!\n");
							break;
						case '2':
							printf("请输入要修改的订单编号：");
							scanf("%s", rt); getchar();
							if (mod_rent(&p1, rt) == OK)
								printf("修改完成！\n");
							else printf("修改出错!\n");
							break;
						case '3':
							printf("请输入要删除的订单编号：");
							scanf("%s", rt); getchar();
							if (del_rent(&p1, rt) == OK)
								printf("删除完成！\n");
							else
								printf("不存在！\n");
							break;
						case '0':break;
						}
					} while (op23 != '0');
					break;
				case '0':break;
				}
			} while (op2 != '0');
			break;
		case '2':			/*数据查询*/
			char op3;
			do {
				printf("------------------------------------------------------------------------------\n");
				printf("1 车辆分类信息查询\n");
				printf("2 车辆基本信息查询\n");
				printf("3 租车订单信息查询 \n");
				printf("4 自由查询                0  退出查询\n");
				printf("------------------------------------------------------------------------------\n");
				printf("请输入你的操作：");
				op3 = getch();
				printf("%c\n", op3);
				switch (op3) {
				case '1': {
					inf_list h_i = (inf_list)malloc(sizeof(inf_node));//保存车辆分类的车辆信息查询结果
					h_i->rent_next = NULL;
					cla_list h1 = (cla_list)malloc(sizeof(cla_node));
					cla_list h1_next = (cla_list)malloc(sizeof(cla_node));
					h1->cla_next = h1_next;
					h1->inf_next = NULL;
					h1_next->inf_next = h_i;
					h1_next->cla_next = NULL;
					char temp311[20];
					int flag = 0; //有没有找到车辆;
					inf_list pt;
					do {
						printf("请输入需要查的车辆类型（输入*  查询全部可租赁车辆）,输入0结束\n");
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
										flag = 1;//找到
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
						printf("----------------------------------查询结果----------------------------------------\n");
						show_inf(h1->cla_next);
						printf("----------------------------------------------------------------------------------\n");
						printf("是否导出本次查询?(y/n): ");
						char out = getch();
						printf("%c\n", out);
						if (out == 'y') {
							printf("请输入导出的文件名: ");
							scanf("%s", pathwrite);
							write_to_csv2(&h1, pathwrite);
						}
					}
					else
						printf("----------------------------------没有找到可用的车辆------------------------------\n");
				}
						break;
				case '2': {
					inf_list h_i = (inf_list)malloc(sizeof(inf_node));//车辆信息查询
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
					printf("请输入要查询的车牌号码(支持模糊查询)，输入*不限: ");//车牌
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
					//后面的内容是对车辆链的修改
					printf("请输入要查询的车辆名称(支持模糊查询)，输入*不限: ");//车辆名称
					scanf("%s", temp312);
					if (temp312[0] != '*') {
							inf_list p1 = h1_next->inf_next;
							int flag1 = 1;//表示相同
							for (int j = 0; j <= (strlen(p1->car_name) - strlen(temp312)); j++) {
								flag1 = 1;
								for (int i = 0; temp312[i] != '\0'; i++) {
									if (p1->car_name[i + j] != temp312[i]) flag1 = 0;//表示有不同
								}
								if (flag1)	break;
							}
							//上面的p1作为后续的头节点,鉴于第一个车辆基本信息结点的特殊性，如果第一个节点p1就不符合要求，那么到最后再修改
							//下面针对中间部分
							inf_list p2 = p1->inf_next;
							while (p2 != NULL) {
								int flag = 1;
								for (int j = 0; j <=(strlen(p2->car_name) - strlen(temp312)); j++) {
									flag = 1;
									for (int i = 0; temp312[i] != '\0'&& p1->car_name[i + j] != '\0'; i++) {
										if (p2->car_name[i + j] != temp312[i]) flag = 0;//表示有不同
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
					printf("请输入要查询的车辆出租状态，y/n   输入*不限: ");//车辆状态
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
					printf("----------------------------------查询结果----------------------------------------\n");
					show_inf(h1_next);
					printf("----------------------------------------------------------------------------------\n");
					printf("是否导出本次查询到文件  车辆基本信息查询结果.csv ? (y/n):  ");
					char out = getch();
					printf("%c\n", out);
					if (out == 'y') {
						write_to_csv2(&h1, path4);
					}
				}
					break;
				case '3':{//租车订单信息查询：思路：以条件创建租车订单链，再完善头节点
					int flag_exit = 0;
					rent_list r_h=(rent_list)malloc(sizeof(rent_node));//租车订单信息的头节点
					rent_list t = r_h;//pr可移动订单指针
					rent_list pt = NULL ;//t的前一个指针
					cla_list p = head->cla_next;//cla遍历指针
					inf_list pi = NULL;//inf指针
					rent_list pr = NULL;//rent指针
					char op33;
					printf("------------------------------------------------------------------------------------\n");
					printf("1  客人信息     2    车辆信息     3   租车时间范围                \n");
					printf("请输入要查找的条件选项: ");
					op33 = getch();
					printf("%c\n", op33);
					if (op33 == '1') {
						char op331;
						printf("1  身份证号        2 手机号                          0 退出            \n");
						printf("请输入要查询的选项：");
						op331 = getch();
						printf("%c\n", op331);
						if (op331 == '1') {
							char t_id[20];
							printf("请输入身份证号：");
							scanf("%s", t_id);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									while (pr != NULL) {
										if (strcmp(pr->person_id, t_id) == 0) {//找到一个合适订单
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
							printf("请输入手机号码：");
							scanf("%s", t_phone);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									while (pr != NULL) {
										if (strcmp(pr->person_phone, t_phone) == 0) {//找到一个合适订单
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
						printf("1  车牌号码        2 车辆名称                                       \n");
						printf("请输入要查询的选项：");
						op332 = getch();
						printf("%c\n", op332);
						if (op332 == '1') {
							char t_license[20];
							printf("请输入车牌号码：");
							scanf("%s", t_license);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									if ( strcmp( pi->car_license_plate_number , t_license ) == 0 ) {//找到合适的车辆
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
							printf("请输入车牌名称：");
							scanf("%s", t_name);
							while (p != NULL) {
								pi = p->inf_next;
								while (pi != NULL) {
									pr = pi->rent_next;
									if (strcmp(pi->car_name, t_name) == 0) {//找到合适的车辆
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
						printf("从（例如20190224）：");
						scanf("%s", t_start);
						t_start[8] = '0';
						t_start[9] = '0';
						t_start[10] = '\0';
						printf("至（例如20190512）：");
						scanf("%s", t_end);
						t_end[8] = '9';
						t_end[9] = '9';
						t_end[10] = '\0';
						while (p != NULL) {
						pi = p->inf_next;
						while (pi != NULL) {
							pr = pi->rent_next;
							while (pr != NULL) {
								if (atoi(pr->rent_number)>=atoi(t_start)&& atoi(pr->rent_number) <= atoi(t_end)){//找到一个合适订单
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
						printf("----------------------------------查询结果----------------------------------------\n");
						show_rent(h3);
						printf("----------------------------------------------------------------------------------\n");
						printf("是否导出本次查询到  租车订单信息查询结果.csv？  (y/n): ");
						char out = getch();
						printf("%c\n", out);
						if (out == 'y') {
							//						printf("请输入导出的文件名: ");
							//						scanf("%s", pathwrite);
							write_to_csv3(&h1, path5);
						}
					}
					else
						printf("--------------------------------不存在该订单--------------------------------------\n");
				}
					break;
				case'4': {
					int flag_exit = 0;	
					rent_list h = (rent_list)malloc(sizeof(rent_node));//租车订单信息的头节点
					rent_list r_h = (rent_list)malloc(sizeof(rent_node));//租车订单信息的第一个点
					h->rent_next = r_h;
					rent_list t = r_h;//pr可移动订单指针
					rent_list pt = NULL;//t的前一个指针
					cla_list p = head->cla_next;//cla遍历指针
					inf_list pi = NULL;//inf遍历指针
					rent_list pr = NULL;//rent遍历指针
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
						printf("-----------------------没有订单-------------------------\n");
					}
					else {
						free(pt->rent_next);
						pt->rent_next = NULL;
						char t_date[20];
						char a[20];
						char b[20];
						printf("请输入日期(*不限):  ");
						scanf("%s", t_date);
						if (t_date[0] != '*') {
							strcpy(a, t_date);
							strcpy(b, t_date);
							a[8] = '0'; a[9] = '0'; a[10] = '\0';
							b[8] = '9'; b[9] = '9'; b[10] = '\0';
							t = h;
							while (t->rent_next != NULL) {
								if (atoi(t->rent_next->rent_number) < atoi(a) || atoi(t->rent_next->rent_number) > atoi(b)) {//不在范围内
									pt = t->rent_next;
									t->rent_next = t->rent_next->rent_next;
									free(pt);
								}
								else t = t->rent_next;
							}
						}
						char t_type[20];
						printf("请输入车辆类型(*不限)：");
						scanf("%s",t_type);
						if (t_type[0] != '*') {
							p = head->cla_next;
							while (p!=NULL&&strcmp(p->car_type, t_type) != 0) {
								p = p->cla_next;
							}
							if (p != NULL) {
								int f1=0;//类别链表有和订单一样的编号车辆标志
								t = h;
								while (t->rent_next != NULL) {
									pi = p->inf_next;
									while (pi != NULL) {
										if (pi->car_number == t->rent_next->car_number) f1 = 1;//有就t将他转移到下一个结点，没有就删除这个结点t->rent_next
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
						printf("请输入车辆名称(*不限)：");
						scanf("%s", t_name);
						char t_pname[20];
						printf("请输入用户姓名(*不限)：");
						scanf("%s", t_pname);
						char t_phone[20];
						printf("请输入用户手机号(*不限)：");
						scanf("%s", t_phone);
						char t_id[20];
						printf("请输入用户身份证号(*不限)：");
						scanf("%s", t_id);
						if (h->rent_next == NULL) {
							printf("------------------------------没找到订单-----------------------------------\n");
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
							printf("----------------------------------查询结果----------------------------------------\n");
							show_rent(i_h);
							printf("----------------------------------------------------------------------------------\n");
							printf("是否导出本次自定义查询？  (y/n): ");
							char out = getch();
							printf("%c\n", out);
							if (out == 'y') {
								printf("请输入导出的文件名: ");
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
		case '3':				/*数据统计*/
			char op4;
			do {
				printf("---------------------------------------------------------------------------------------\n");
				printf("统计选项：\n");
				printf("    1  当前当前每种车辆类型的车辆总数、已出租数、未出租数\n");
				printf("    2  统计每月每种车辆类型的营业额（产生的实缴费用），输出当月每种车辆类型的营业额柱状统计图\n");
				printf("    3  输入年份，统计该年每辆车的营业额（产生的实缴费用）、租用率\n");
				printf("    4  列出当年来累计出租天数最多的10辆车的出租信息，按累计出租天数降序排序后输出。\n   （身份证号、姓名、累计租房月数、应缴住宿费总额、实缴住宿费总额\n");
				printf("    0  退出\n");
				printf("---------------------------------------------------------------------------------------\n");
				printf("请输入要选择的统计：");
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
					printf("---------------------------------------统计结果---------------------------------------\n");
					printf("  车辆类型              车辆总数                已出租数                未出租数          \n");
					printf("  经济型                  %2d                      %2d                    %2d                 \n", num[0], num_y[0], num[0] - num_y[0]);
					printf("  商务型                  %2d                      %2d                    %2d                 \n", num[1], num_y[1], num[1] - num_y[1]);
					printf("  豪华型                  %2d                      %2d                    %2d                 \n", num[2], num_y[2], num[2] - num_y[2]);
					printf("  SUV                     %2d                      %2d                    %2d                 \n", num[3], num_y[3], num[3] - num_y[3]);
					printf("  7座及以上车型           %2d                      %2d                    %2d                 \n", num[4], num_y[4], num[4] - num_y[4]);
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
					printf("---------------------------------------统计结果---------------------------------------\n");
					printf("  车辆类型                       营业额                                                      \n");
					printf("  经济型                   %10.2f                                                        \n", w[0]);
					printf("  商务型                   %10.2f                                                        \n", w[1]);
					printf("  豪华型                   %10.2f                                                        \n", w[2]);
					printf("  SUV                      %10.2f                                                        \n", w[3]);
					printf("  7座及以上车型            %10.2f                                                        \n", w[4]);
					printf("--------------------------------------------------------------------------------------\n");
					printf("是否输出图形(y/n):");
					char t_1;
					t_1 = getch();
					printf("%c\n任意键退出图形\n", t_1);
					if(t_1=='y') {
						int i, j;
						initgraph(640, 480, SHOWCONSOLE); // 创建一个宽 640 x 高 480 像素的窗口
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
						// 1.设置文字背景模式为 TRANSPARENT 实现输出文字无背景色
						settextcolor(RGB(0, 0, 0));
						// 2.设置文字颜色为 红色
						settextstyle(15, 0, _T("宋体"));
						// 3.设置文字大小和字体，参数依次为：高、宽、字体。若宽度为 0 表示自适应,
						// 字体_T(“*” )中*可自行替换，建议使用常见的字体，如：宋体、楷体、隶书等
						outtextxy(50, 95, _T("6000"));
						outtextxy(50, 145, _T("5000"));
						outtextxy(50, 195, _T("4000"));
						outtextxy(50, 245, _T("3000"));
						outtextxy(50, 295, _T("2000"));
						outtextxy(50, 345, _T("1000"));
						outtextxy(50, 395, _T("0"));
						outtextxy(120, 410, _T("经济型"));
						outtextxy(200, 410, _T("商务型"));
						outtextxy(280, 410, _T("豪华型"));
						outtextxy(360, 410, _T("SUV"));
						outtextxy(440, 410, _T("7座及以上车型"));
						for (int i2 = 0; i2 < 5; i2++) {
							setfillstyle(BS_SOLID);
							// 1.设置当前填充样式为固实
							setfillcolor(RGB(0, 0, 0));
							// 2.设置当前填充颜色为黑色
							int a1 = w[i2] / 20;
							wchar_t temp[100];
							_stprintf_s(temp, _T("%.1f"), w[i2]);
							outtextxy(120 + i2 * 80, 400 - a1 - 20, temp);
							solidrectangle(120 + i2 * 80, 400 - a1, 120 + i2 * 80+40, 400);
							// 3.绘制无外框的填充矩形, 左上角坐标（10,20），右下角坐标（100,120）
							// 4.输出不带背景的文字,在坐标(20,30)处输出 Hello World!展示输出字符常量内容
						}
						getchar(); // 暂停程序运行，查看输出结果
						closegraph();// 关闭图形界面
					}
				}
					break;
				case '3': {
					int i;
					char s_year[20];
					printf("请输入年份：");
					scanf("%s", s_year);
					char before[20];//year000000
					char after[20];//year999999订单号限制二者之间即可
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
					printf("----------------------------------%s年-----------------------------------\n",s_year);
					printf("  车牌号         车辆名称                   营业额            租用率       \n");
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
					printf("                           营业总额: %f                  \n",saleall);
					printf("--------------------------------------------------------------------------------\n");
				}
					break;
				case '4': {//按顺序记录每个节点的租用时间，同时创造一条车辆信息单链，绑定数组和车辆，并发进行冒泡排序，得到降序序列
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
							*t = *it;//复制内容
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
					pt->inf_next = NULL;//车辆单向链表完成
					//day[0]即第一个的时间，以此类推
					//下面是冒泡排序算法
					int flag;
					inf_list ch = (inf_list)malloc(sizeof(inf_node));
					ch->inf_next = car_list;
					ch->rent_next = NULL;
					do {
						i = 0;flag = 0;
						inf_list p1 = ch;
						inf_list p2 = ch->inf_next;
						while (p2->inf_next != NULL) {//p2是第一个结点，p1是头节点
							if (day[i] < day[i + 1]) {
								flag = 1;//表示没排完，还在操作
								p1->inf_next = p1->inf_next->inf_next;//结点排序
								p2->inf_next = p2->inf_next->inf_next;
								p1->inf_next->inf_next = p2;
								int temp = day[i];//交换租用时间
								day[i] = day[i + 1];
								day[i + 1] = temp;
							}
							p1 = p1->inf_next;
							p2 = p2->inf_next;
							i++;
						}

					} while (flag == 1);
					printf("---------------------------------------------------------------------------------------------\n");
					printf("车牌号                    车辆名称            累计出租天数         营业额          租用率     \n");
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
		case '4':			/*数据导入导出*/
			char op1;
			do {
				printf("1  数据导入             2  数据导出          0  退出 \n");
				op1 = getch();
				printf("%c\n", op1);
				switch (op1) {
				case '1':
					if (get_from_csv1(&head, path1) == OK && get_from_csv2(&head, path2) == OK && get_from_csv3(&head, path3) == OK) {
						printf("-----------------------------已载入-----------------------------------\n");
					}
					else {
						printf("导入文件为空\n");
					}
					break;

				case '2':
					if (write_to_csv1(&head, path1) == OK && write_to_csv2(&head, path2) == OK && write_to_csv3(&head, path3) == OK) {}
					else {
						printf("导出文件失败，请重新调试\n");
						return ERROR;
					}
					break;
				}
			} while (op1 != '0');
			break;
		case '0':
			printf("--------------------------- 感谢使用！----------------------------------- \n");
			break;
		}
	}while (op != '0');

	/*自动保存*/
	if (write_to_csv1(&head, path01) == OK && write_to_csv2(&head, path02) == OK && write_to_csv3(&head, path03) == OK) {
		printf("------------------------------------------------------------------------------\n");
		printf("-----------------------------本次dat数据已保存--------------------------------\n");
	}

	free_cla(&head);
	return 0;
}