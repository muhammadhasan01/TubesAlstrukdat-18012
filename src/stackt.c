/* Program          : stackt.c */
/* Deskripsi        : Implementasi Stackt */
/* Definisi Stack   : Model Implementasi dengan tabel kontigu dan ukuran sama */

#include "stackt.h"
#include "string.h"
#include <stdio.h>

// $ ************ Prototype ************
// $ *** Konstruktor/Kreator ***
void StartTurn(Stack *S, Player P1, Player P2, int Turn, Bangunan DataBuild) {
    Top(*S) = 1;
    P1Info(InfoTop(*S)) = P1;
    P2Info(InfoTop(*S)) = P2;
    TurnInfo(InfoTop(*S)) = Turn;
    DataB(InfoTop(*S)) = DataBuild;
}
void ClearStack(Stack *S) {
    Sinfotype temp;
    while(!IsFirstAct(*S)) {
        puts("PASS");
        Pop(S,&temp);
    }
}

// $ ************ Predikat Untuk test keadaan KOLEKSI ************
boolean IsFirstAct(Stack S) {
    return ((Top(S)-1) == SNil);
}

boolean IsFull(Stack S) {
    return (Top(S) == MaxSEl);
}

// $ ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack *S, Sinfotype X) {
    Top(*S) += 1;
    InfoTop(*S) = X;
}

// $ ************ Menghapus sebuah elemen Stack ************
void Pop(Stack *S, Sinfotype *X) {
    *X = InfoTop(*S);
    Top(*S) -= 1;
}

// $ ************ Turn Handling ************

Player GetTopPlayer(Stack S) {
    if (TurnInfo(InfoTop(S)) == 1) {
        return (P1Info(InfoTop(S)));
    } else if (TurnInfo(InfoTop(S)) == 2) {
        return (P2Info(InfoTop(S)));
    }
}

void ChangeTurn(Stack *S, Bangunan *B) {
    // $ Kamus Lokal
    Player *TopP, *EnemyP;
    List *Ltop, *Lenemy;
    if (TurnInfo(InfoTop(*S)) == 1) {
        TopP = &P1Info(InfoTop(*S));
        EnemyP = &P2Info(InfoTop(*S));
    } else {
        TopP = &P2Info(InfoTop(*S));
        EnemyP = &P1Info(InfoTop(*S));
    }
    Ltop = &ListBan(*TopP);
    Lenemy = &ListBan(*EnemyP);
    // $ Algoritma
    if (!ET(FX(*TopP))) {
        TurnInfo(InfoTop(*S)) = TurnInfo(InfoTop(*S)) % 2 + 1;
        //printf("Changing turns"); sleep(1);printf(".");sleep(1);printf(".");sleep(1);printf("\n\n");
    }
    // ! Reset FX Extra Turn
    ET(FX(*TopP)) = false;
    // ! Reset FX Attack Up
    AU(FX(*TopP)) = false;
    // ! Reduce Shield
    ReduceDurationSH(EnemyP);
    // * Clear Stack
    ClearStack(S);
}

void PrintCurr(Stack S) {
    // $ Kamus Lokal
    Player TopP = GetTopPlayer(S);
    Bangunan DataBuild = DataB(InfoTop(S));
    List Ltop = ListBan(TopP);
    // $ Algoritma
    printf("[] ==== ==== ====  Player %d  ==== ==== ==== []\n\n", TurnInfo(InfoTop(S))),
    //printbuilding
    printf("  <= Active Effects =>\n");
    printf("<> == <> == <> == <> == <>   [] ===== [] == []\n ");
    if (AU(FX(TopP))) printf(" [AU] "); else printf(" [  ] ");
    if (CH(FX(TopP))) printf(" [CH] "); else printf(" [  ] ");
    if (ActiveSH(SH(FX(TopP)))) printf(" [SH] "); else printf(" [  ] ");
    if (ET(FX(TopP))) printf(" [ET] "); else printf(" [  ] ");
    printf("    || SKILL ");
    PrintQueue(Skill(TopP));
    printf("\n");
    printf("<> == <> == <> == <> == <>   [] ===== [] == []\n");
    printf("\n");
    printf(" __\n[__] ==== Daftar Bangunan ==== [P%d]\n", TurnInfo(InfoTop(S)));
    PrintInfo(Ltop, DataBuild);
    printf("\n");
}
void PrintTop(Sinfotype top)
{   
    // $ Kamus Lokal
    Player TopP;
    if (TurnInfo(top) == 1) {
        TopP = P1Info(top);
    } else {
        TopP = P2Info(top);
    }
    Bangunan DataBuild = DataB(top);
    List Ltop = ListBan(TopP);
    // $ Algoritma
    printf("[] ==== ==== ====  Player %d  ==== ==== ==== []\n\n", TurnInfo(top)),
        //printbuilding
        printf("  <= Active Effects =>\n");
    printf("<> == <> == <> == <> == <>   [] ===== [] == []\n ");
    if (AU(FX(TopP)))
        printf(" [AU] ");
    else
        printf(" [  ] ");
    if (CH(FX(TopP)))
        printf(" [CH] ");
    else
        printf(" [  ] ");
    if (ActiveSH(SH(FX(TopP))))
        printf(" [SH] ");
    else
        printf(" [  ] ");
    if (ET(FX(TopP)))
        printf(" [ET] ");
    else
        printf(" [  ] ");
    printf("    || SKILL ");
    PrintQueue(Skill(TopP));
    printf("\n");
    printf("<> == <> == <> == <> == <>   [] ===== [] == []\n");
    printf("\n");
    printf(" __\n[__] ==== Daftar Bangunan ==== [P%d]\n", TurnInfo(top));
    PrintInfo(Ltop, DataBuild);
    printf("\n");
}
