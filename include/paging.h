/* paging.h --> 分页相关物的声明 */
/* Copyright (c) 1998 著作权由Chapaev所有。著作权人保留一切权利。
 * 
 * 这份授权条款，在使用者符合以下三条件的情形下，授予使用者使用及再散播本
 * 软件包装原始码及二进位可执行形式的权利，无论此包装是否经改作皆然：
 * 
 * * 对于本软件源代码的再散播，必须保留上述的版权宣告、此三条件表列，以
 *   及下述的免责声明。
 * * 对于本套件二进位可执行形式的再散播，必须连带以文件以及／或者其他附
 *   于散播包装中的媒介方式，重制上述之版权宣告、此三条件表列，以及下述
 *   的免责声明。
 * * 未获事前取得书面许可，不得使用本软件贡献者之名称，
 *   来为本软件之衍生物做任何表示支持、认可或推广、促销之行为。
 * 
 * 免责声明：本软件是由本软件之贡献者以现状（"as is"）提供，
 * 本软件包装不负任何明示或默示之担保责任，包括但不限于就适售性以及特定目
 * 的的适用性为默示性担保。加州大学董事会及本软件之贡献者，无论任何条件、
 * 无论成因或任何责任主义、无论此责任为因合约关系、无过失责任主义或因非违
 * 约之侵权（包括过失或其他原因等）而起，对于任何因使用本软件包装所产生的
 * 任何直接性、间接性、偶发性、特殊性、惩罚性或任何结果的损害（包括但不限
 * 于替代商品或劳务之购用、使用损失、资料损失、利益损失、业务中断等等），
 * 不负任何责任，即在该种使用已获事前告知可能会造成此类损害的情形下亦然。*/

#ifndef __ATOMIC_PAGING_H__
#define __ATOMIC_PAGING_H__

#include <isr.h>

typedef struct Page
{
	u32i Present : 1;
	u32i ReadWrite : 1;
	u32i User : 1;
	u32i Accessed : 1;
	u32i Dirty : 1;
	u32i Unused : 7;
	u32i Frame : 20;
} PageType;

typedef struct PageTable
{
	PageType Pages[1024];
} PageTableType;

typedef struct PageDirectory
{
	PageTableType* Tables[1024];
	u32i TablesPhysical[1024];
	u32i PhysicalAddress;
} PageDirectoryType;

void InitialisePaging();
void SwitchPageDirectory(PageDirectoryType* NewDirectory); 
PageType* GetPage(u32i Address,int Make,PageDirectoryType* Directory);
void PageFault(RegistersType Registers);
void MapPage(u32i Address);
void* GetFreePages(u32i HowMany);
void ReturnPages(void* Address,u32i HowMany);

#endif //__ATOMIC_PAGING_H__
	
