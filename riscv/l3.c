#include<stdio.h>
#include<stdlib.h>
int opcode(int decimal){
    int x=(decimal<<25)>>25;
    x=x&127;
    return x;
}
int funct3(int decimal){
    int x=(decimal<<17)>>29;
    x=x&7;
    return x;
}
int funct7(int decimal){
    int x=(decimal>>25)&127;
    return x;
}
int funct6(int decimal){
    int x=(decimal>>26)&63;
    return x;
}
int rdest(int decimal){
    int x=(decimal<<20)>>27;
    x=x&31;
    return x;
}
int rsource1(int decimal){
    int x=(decimal<<12)>>27;
    x=x&31;
    return x;
}
int rsource2(int decimal){
    int x=(decimal<<7)>>27;
    x=x&31;
    return x;
}
int bimm(int decimal){
    int x=(decimal>>8)&15;
    int y=((decimal<<1)>>26)&63;
    int z=(decimal>>7)&1;
    int w=(decimal>>31);
    y=y<<4;
    z=z<<10;
    w=w<<11;
    x=(x+y+z+w)<<1;
    return x;
}
int iimm(int decimal){
    int x=(decimal>>20);
    return (int)x;
}
int iimm2(int decimal){
    int x=((decimal<<6)>>26)&63;
    return (int)x;
}
int simm(int decimal){
    int x=(decimal>>7)&31;
    int y=(decimal>>25);
    y=y<<5;
    x=x+y;
    return (int)x;
}
int jimm(int decimal){
    int x=((decimal<<1)>>22)&1023;
    int y=((decimal<<11)>>31)&1;
    int z=((decimal<<12)>>24)&255;
    int w=((decimal>>31));
    y=y<<10;
    z=z<<11;
    w=w<<19;
    x=x+y+z+w;
    x=x<<1;
    return (int)x;
}
int uimm(int decimal){
    int x=(decimal>>12);
    return (int)x;
}
int arr[1000];
int j=0,k=0;
void printlabel(int pc){
    for (int i = 0; i < j; i++) {
        if (pc == arr[i]) {
            printf("L%d:", i + 1);
        }
    }
}
void instruction(int decimal,int pc){
    int op=opcode(decimal);
    int f3,f7,rd,rs1,rs2,imm,f6;
    if(op==51){
        f3=funct3(decimal);
        f7=funct7(decimal);
        rd=rdest(decimal);
        rs1=rsource1(decimal);
        rs2=rsource2(decimal);
        if(f3==0 && f7==0){
            printf("add x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==0 && f7==32){
            printf("sub x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==4){
            printf("xor x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==6){
            printf("or x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==7){
            printf("and x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==1){
            printf("sll x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==5 && f7==0){
            printf("srl x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==5 && f7==32){
            printf("sra x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==2){
            printf("slt x%d,x%d,x%d\n",rd,rs1,rs2);
        }
        if(f3==3){
            printf("sltu x%d,x%d,x%d\n",rd,rs1,rs2);
        }
    }
    if(op==19 || op==3 || op==103){
        f3=funct3(decimal);
        rd=rdest(decimal);
        rs1=rsource1(decimal);
        imm=iimm(decimal);
        if(op==19){
            if(f3==0){
                printf("addi x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==4){
                printf("xori x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==6){
                printf("ori x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==7){
                printf("andi x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==1){
                imm=iimm2(decimal);
                printf("slli x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==5){
                f6=funct6(decimal);
                imm=iimm2(decimal);
                if(f6==0){
                    printf("srli x%d,x%d,%d\n",rd,rs1,imm);
                }
                if(f6==16){
                    printf("srai x%d,x%d,%d\n",rd,rs1,imm);
                }
            }
            if(f3==2){
                printf("slti x%d,x%d,%d\n",rd,rs1,imm);
            }
            if(f3==3){
                printf("sltiu x%d,x%d,%d\n",rd,rs1,imm);
            }
        }
        if(op==3){
            if(f3==0){
                printf("lb x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==1){
                printf("lh x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==2){
                printf("lw x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==3){
                printf("ld x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==4){
                printf("lbu x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==5){
                printf("lhu x%d,%d(x%d)\n",rd,imm,rs1);
            }
            if(f3==6){
                printf("lwu x%d,%d(x%d)\n",rd,imm,rs1);
            }
        }
        if(op==103){
            if(f3==0){
                printf("jalr x%d,%d(x%d)\n",rd,imm,rs1);
            }
        }
    }
    if(op==35){
        rs1=rsource1(decimal);
        rs2=rsource2(decimal);
        imm=simm(decimal);
        f3=funct3(decimal);
        if(f3==0){
            printf("sb x%d,%d(x%d)\n",rs2,imm,rs1);
        }
        if(f3==1){
            printf("sh x%d,%d(x%d)\n",rs2,imm,rs1);
        }
        if(f3==2){
            printf("sw x%d,%d(x%d)\n",rs2,imm,rs1);
        }
        if(f3==3){
            printf("sd x%d,%d(x%d)\n",rs2,imm,rs1);
        }           
    }
    if(op==99){
        rs1=rsource1(decimal);
        rs2=rsource2(decimal);
        f3=funct3(decimal);
        imm=bimm(decimal);
        k=pc;
        int d=0;
        arr[j]=pc+(imm/4);
        int i,l;
        for( i=j;i>0;i--){
            if(arr[j]==arr[i-1]){
                d=1;
                l=i;
                break;
            }
        }
        if(d==0){
            j++;
            l=j;
        }
        if(f3==0){
            printf("beq x%d,x%d,L%d\n",rs1,rs2,l);
        }
        if(f3==1){
            printf("bne x%d,x%d,L%d\n",rs1,rs2,l);
        }
        if(f3==4){
            printf("blt x%d,x%d,L%d\n",rs1,rs2,l);
        }
        if(f3==5){
            printf("bge x%d,x%d,L%d\n",rs1,rs2,l);
        }
        if(f3==6){
            printf("bltu x%d,x%d,L%d\n",rs1,rs2,l);
        }
        if(f3==7){
            printf("bgeu x%d,x%d,L%d\n",rs1,rs2,l);
        }        
    }
    if(op==111){
        rd=rdest(decimal);
        imm=jimm(decimal);
        k=pc;
        int c=0;
        arr[j]=pc+(imm/4);
        int l;
        for(int i=j;i>0;i--){
            if(arr[j]==arr[i-1]){
                c=1;
                l=i;
                break;
            }
        }
        if(c==0){
            j++;
            l=j;
        }
        printf("jal x%d,L%d\n",rd,l);
    }
    char hex[100];
    if(op==55){
        imm=uimm(decimal);
        sprintf(hex,"%x",imm);
        rd=rdest(decimal);
        printf("lui x%d,0x%s\n",rd,hex);
    }
}
int main(){
    FILE *file;
    char filename[100];
    printf("Enter the filename:");
    scanf("%s",filename);
    char line[100];
    file = fopen(filename,"r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int pc=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        unsigned int decimal = strtol(line, NULL,16);
        printlabel(pc);
        instruction(decimal,pc);
        pc++;
    }
}