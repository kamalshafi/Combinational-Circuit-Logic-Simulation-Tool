#include "input.h"
/***************************************************************************************************************************
Truth Table
****************************************************************************************************************************/
int NOTG[5] = {1,0,DC,Db,D};
int ANDG[5][5]={{0,0,0,0,0},{0,1,DC,D,Db},{0,DC,DC,DC,DC},{0,D,DC,D,0},{0,Db,DC,0,Db}};
int ORG[5][5]={{0,1,DC,D,Db},{1,1,1,1,1},{DC,1,DC,DC,DC},{D,1,DC,D,1},{Db,1,DC,1,Db}};
int NOC[10]={0,0,0,0,0,1,1,0,0,0};
int fault[3][3]={{0,D,DC},{Db,1,DC},{DC,DC,DC}};

int ReadPat(FILE *Pat, PATTERN *Patterns){   // Function for reading patterns
	char line[Mlin];//Local Variable having a array of size of Mlin
	int i=0,n;
	// read line by line
	while(!feof(Pat)){
		if(fgets(line,Mlin,Pat)!=NULL){
			// printf("%s",line);
			for(n=0;n<strlen(line);n++){
				if(line[n]=='1')
					Patterns[i].Pat[n]=1;
				else if(line[n]=='0')
					Patterns[i].Pat[n]=0;
				else if(line[n]=='x'||line[n]=='X')
					Patterns[i].Pat[n]=DC;
			}
			i++;
		}
	}

	// for(n=0;n<5;n++){
	//	for(i=0;i<5;i++)	printf("%d",Patterns[n].Pat[i]);
	//	printf("\n");
	// }
	return i;
}

void LogicSim(GATE *Node, PATTERN *Patterns, int Tgat, int Tpat, FILE *Res) //Function for running Logic Simulation
{
	int i,j,k;

	for(i=0;i<Tpat;i++){
		k=0;
		for(j=0;j<=Tgat;j++){
			if(Node[j].Type !=0){
				if(Node[j].Type==INPT){
					Node[j].Val = Patterns[i].Pat[k];
					k++;
				}
				else{
					Gout(Node, j);
				}
				if(Node[j].Po) {
					printf("%d",Node[j].Val);
					if(Node[j].Val==2)
						fputc('x', Res);
					else
						fputc(Node[j].Val+'0' , Res);
				}
			}
		}//PrintGats(Node,Tgat); 
		printf(" %d\n", i); // Printing output corresponding Number
		fputc('\n' , Res);
		
	}
}

void Gout(GATE *Node, int a) //Function for gate outputs
{
	LIST *lfin;
	int val; // local variable
	if(Node[a].Type==FROM){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==BUFF){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=Node[lfin->Id].Val; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==NOT){
		lfin=Node[a].Fin;
		while(lfin!=NULL){
			Node[a].Val=NOTG[Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
	}
	else if(Node[a].Type==AND){
		lfin=Node[a].Fin;
		val=1;// non control for AND gate
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=val;
	}
	else if(Node[a].Type==NAND){
		lfin=Node[a].Fin;
		val=1;// non control for AND gate
		while(lfin!=NULL){
			val=ANDG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		}
		Node[a].Val=NOTG[val]; //Inverting AND Operation
	}
	else if(Node[a].Type==OR){
		lfin=Node[a].Fin;
		val=0;// non control for OR gate
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=val;
	}
	else if(Node[a].Type==NOR){
		lfin=Node[a].Fin;
		val=0;// non control for OR gate
		while(lfin!=NULL){
			val=ORG[val][Node[lfin->Id].Val]; 
			lfin=lfin->Next;
		 }
		Node[a].Val=NOTG[val];//Inverting OR Operation
	}
	else if(Node[a].Type==XOR) {printf("ERROR: XOR GATE FOUND\n");exit(0);}
	else if(Node[a].Type==XNOR){printf("ERROR: XNOR GATE FOUND\n");exit(0);}
}

/***************************************************************************************************/

