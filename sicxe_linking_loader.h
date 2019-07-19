#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  //---------------check the gcc compile warning------------
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE_COMND 50

typedef struct c_node {
	char comnd[MAX_SIZE_COMND];
	unsigned int seq; //refers sequence number in LinkedList or opcode number in hashtable
	char format[8];
	struct c_node *next;
}Node;

typedef struct _List {
	Node * first;
	Node * cur;
}LinkedList;

typedef struct _hash {
	char data;
	Node * next;
}Hash;

typedef struct _assem {
	char code[4][64];
	int word_num;
	unsigned int assign_address;
	unsigned int object_code;
	char objcode_string[64];
	char *comment;
	int line_number;
	char index;
	char format;
}Assemcode;

typedef struct _extdef {
	char name[7];
	unsigned int address;
}extDef;

typedef struct _extref {
	int index;
	char name[7];
}extRef;
typedef struct _cs {
	char name[7];
	int address;
	int length;
	extDef extdef[6];
	extRef extref[12];
}ControlSection;

typedef struct _est {
	char cs[7];
	char symname[7];
	int address;
	int length;
}Estab;

int checkright(char* inp);
int balancer(int comndnum, char *arg[], int argnum, Assemcode *assemcode, LinkedList *hist, Hash * optable, Hash **symtable, Hash **newSymtab, unsigned char *mem);
void help(void);
void dir(void);
void history(LinkedList *hist);
void addLlist(LinkedList *hist, Hash *table, char **inpcomnd, int mode);
void dump(char *arg[], int argnum, unsigned char *mem);
void dumpprint(int *range, unsigned char*mem);
int exponhex(int x);
int converthex(char *arg);
int edit(char *arg[], unsigned char *mem); //수정7
int fill(char *arg[], unsigned char *mem);
void reset(unsigned char *mem);
int opcodesearch(char *arg[], Hash *table, Node **opcode, int mode);
int ophashMake(Hash *table);
int ophashindex(char *opname);
int opcodelist(Hash *table);
int letterfilter(char *inpcmnd, int i, int *blankflag, int *breakflag);
void freemalloc(Assemcode *assemcode, LinkedList *hist, Hash * optable, Hash *symtab, unsigned char *mem);
int expondec(int x);
int assemPassOne(char filename[], Assemcode *assemcode, Hash **newSymtab, Hash *optable);
int formatCal(char word_opcode[], Node * opcode, int Locctr);
int checkSymbol(Hash *symtab, char *word, int Locctr);
int hashSymbol(char *word);
int assemLetterFilter(char *inpcmnd, int index, int *blankflag, int *breakflag);
int assemPassTwo(Assemcode *assemcode, Hash **newSymtab, Hash * optable);
void symtabPrint(Hash *symtab);
void addressRef(Assemcode *assemcode, int codeline, int *n_flag, int *i_flag);
int convertFlag(int n_flag, int i_flag, int b_flag, int p_flag, int e_flag);
int charToDecimal(char *word);
int convertConstant(char *word);
int returnReg(char *word);
void writeListFile(Assemcode *assemcode, char *filename, int codeline);
void writeObjectCode(Assemcode *assemcode, char *filename, int codeline, int locctr);
void valToCharWord(char *print_buf);
int type(char *filename);
void zeroRender(char *print_buf, int size);
int searchEstab(int mode, char *word, ControlSection controlSection);
void estabPrint(void);
int loader(char *obj_files[], int num_files, unsigned char *mem);
int progaddrSet(char *address);
int breakpoint(char *arg, int argnum);
int bp_check(int pc);
int run(unsigned char *mem);

extern int lastaddress;
extern int opflag;
extern int symflag;//추가
extern int base_addressing;
extern int subrout_num; //recording subroutin numbers for new line for text record, initialzied in pass one
extern int direct_num; //recording direct addressing number for modification record, initialized in pass two
extern int progaddr;
extern int bp[20];
extern int bp_valid[20];
extern int bp_num;
extern Estab estab[21]; // maximum cs number 3 + max extdef num for each cs 6 * 3 = 21
extern int load_flag;
extern int reg[7];
extern int bpflag;
extern int endaddress, startaddress;