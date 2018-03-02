
#include "list.h"

// 初始化链表
void init(plist_t pl)
{
	pl->head.next = NULL;
	pl->len = 0;
}

// 按值查找
pnode_t find(plist_t pl, pelem_t pe)
{
	pnode_t pnode = pl->head.next;

	// 从链表头开始一个一个结点比对元素值
	while (pnode)
	{
		// 找到元素
		if (pnode->data == *pe)
		{
			break;
		}
		// 未找到元素，则指向下一个
		pnode = pnode->next;
	}

	// 返回结点指针，如果未找到，或者链表为空，就返回 NULL
	return pnode;
}

// 从头插入，特点：最后插入的结点在最前面
void insert_head(plist_t pl, pelem_t pe)
{
	// 为新元素分配结点空间
	pnode_t pnode = (pnode_t) malloc(sizeof (node_t));

	// 新元素存入结点
	pnode->data = *pe;

	// 将结点插入链表头
	pnode->next = pl->head.next;
	pl->head.next = pnode;

	// 长度自增
	pl->len++;
}

// 从尾插入，特点：链表中按插入的顺序排列
void insert_tail(plist_t pl, pelem_t pe)
{
	pnode_t pt = &pl->head;
	// 为新元素分配结点空间
	pnode_t pnode = (pnode_t) malloc(sizeof (node_t));
	
    // 新元素存入结点
    pnode->data = *pe;
	pnode->next = NULL;  // 最后结点的 next 域必须为 NULL

	// 找到尾部结点
	while (pt->next)
	{
		pt = pt->next;
	}
	// 插入到尾部
	pt->next = pnode;

	// 长度自增
	pl->len++;
}

// 从头删除
// 返回值：1 删除成功，0 删除失败
int delete_head(plist_t pl, pelem_t pe)
{
	pnode_t pnode = pl->head.next;

	// 链表为空则删除失败
	if (is_empty(pl))
	{
		return 0;
	}

	// 取出元素值
	*pe = pnode->data;

	// 从链表头删除头结点
	pl->head.next = pnode->next;

	// 销毁删除的结点
	free(pnode);

	// 长度自减
	pl->len--;

	// 返回成功
	return 1;
}

// 作业：从尾删除 
// 作业：清空链表
// 作业：反转链表
// 作业：复制链表，即根据原链表创建一个新链表

// 遍历链表
void print(plist_t pl)
{
	pnode_t pnode = pl->head.next;

	while (pnode)
	{
		printf("%d  ", pnode->data);
		pnode = pnode->next;
	}

	printf("\n");
}

// 无序链表的无序合并
// 将 la 和 lb 合并到 lc，先合并 la，再合并 lb
void merge(plist_t lc, plist_t la, plist_t lb)
{
	pnode_t pt = NULL;

	// 先将 la 合并到 lc
	lc->head.next = la->head.next;
	la->head.next = NULL;  // 断开 la 与原头结点
	
	// 再找到 lc 的尾部结点
	pt = &lc->head;
	while (pt->next)
	{
		pt = pt->next;
	}
	// 最后将 lb 合并到 lc 尾部
	pt->next = lb->head.next;
	lb->head.next = NULL;

	// 设置 lc，la，lb 长度
	lc->len = la->len + lb->len;
	la->len = 0;
	lb->len = 0;
}

// 有序链表的有序合并
// 将两个有序（升序）链表 la 和 lb 合并到 lc
void merge_order(plist_t lc, plist_t la, plist_t lb)
{
	pnode_t pa = la->head.next, pb = lb->head.next, pc = &lc->head;
	
	// 当两个表都没结束时，进行结点的合并
	while (pa && pb)
	{
		if (pa->data < pb->data)
		{
			la->head.next = pa->next;
			pc->next = pa;
			pa = la->head.next;
		}
		else
		{
			lb->head.next = pb->next;
			pc->next = pb;
			pb = lb->head.next;
		}
		pc = pc->next;
	}
	// 将没有结束的表的剩余部分合并到 lc
	if (pa)
	{
		pc->next = pa;
		la->head.next = NULL;
	}
	if (pb)
	{
		pc->next = pb;
		lb->head.next = NULL;
	}
	// 设置长度
	lc->len = la->len + lb->len;
	la->len = 0;
	lb->len = 0;
}

// 判断链表是否为空
// 返回值：1 表空，0 表非空
int is_empty(plist_t pl)
{
	return pl->len == 0;
}

