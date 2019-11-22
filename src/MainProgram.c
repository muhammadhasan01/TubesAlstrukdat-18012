/* Tubes AlStrukDat */
/* Kelompok 8 */
/* Anggota:
/* - Muhammad Hasan           - 13518012 */
/* - Anna Elvira Hartoyo      - 13518045 */
/* - Daniel Riyanto           - 13518075 */
/* - Faris Muhammad Kautsar   - 13518105 */
/* - Gregorius Jovan Kresnadi - 13518135 */
/* File : MainProgram.c */
/* Program Utama */
/* *
* Nama Program: Avatar World War

* Game Avatar World War adalah game​ turn-based strategy yang
* mensimulasikan perang dunia. Game ini dimainkan dengan cara
* memasukkan perintah melalui command line interface.
 */
// $ ******* INCLUDE FILES ********
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes.c"
#include "string.h"

// $ ***** Variables *****
char menu[100];
boolean Exit; // = false;
boolean ExitMenu; // = false;
boolean EndTurn; // = false;

// $ ******* MAP PRINTING FUNCTION ********
void PrintMap(MATRIKS M, Bangunan B, Player One, Player Two) {
    int i, j;
    for (i = 1; i <= (MaxBrs(M) + 2); i++) {
        for (j = 1; j < (MaxKol(M) + 3); j++) {
            //printf("%d%d",i,j);
            if (i == 1) {
                printf("+");
                if(j == (MaxKol(M) + 2)) {
                    printf("++\n");
                }
            }
            else if (i == (MaxBrs(M) + 2)) {
                printf("+");
                if(j == (MaxKol(M) + 2)) printf("++\n");
            }
            else if (j == 1) {
                printf("+ ");
            }
            else if (j == (MaxKol(M) + 2)) {
                printf(" +\n");
            }
            else if ((Elmt(M,(i-1),(j-1))) == 0) {
                printf(" ");
            }
            else {
                ElType Mem = Elmt(M,(i-1),(j-1));
                char C = Name(ElmtBan(B,Mem));
                if (Search(ListBan(One), Mem) != Nil) {
                    print_warna(Color(One), C);
                }
                else if (Search(ListBan(Two), Mem) != Nil) {
                    print_warna(Color(Two), C);
                }
                else {
                    printf("%c", C);
                }
            }
        }
    }
    printf("\n");
}


// $ ******* MAIN PROGRAM ********
int main() {
do {
    Exit = false;
    MainM();
    // ASCII Art: MainMenu
    do {
        ExitMenu = false;
        Menu();
        // Lakukan Input dengan 'mesinkata'
        int idxMenu = 0;
        do {
            scanf("%c", menu + idxMenu);
        } while (menu[idxMenu++] != '\n');
        menu[--idxMenu] = '\0';
        //printf("Your choice is %s\n",menu);
        //getchar();

            // $ ######### TUTORIAL ########
        if (strcmpi(menu,"TUTORIAL") == 0) {
            printf("\n");
            // todo Tutorial1();
            clrscrn();
            printf("#TUT1 PLACEHOLDER#\n");
            getchar();
            clrscrn();
            // todo Tutorial2();
            printf("#TUT2 PLACEHOLDER#\n");
            getchar();
            clrscrn();
            ExitMenu = true;

        }   // $ ######### CREDITS ########
        else if (strcmpi(menu, "CREDITS") == 0) {
            Credits();
            printf("\n");
            printf("Press enter to go back to the main menu...");
            getchar();
            ExitMenu = true;

        }   // $ ######### QUIT ########
        else if (strcmpi(menu, "QUIT") == 0) {
            QuitImg();
            ExitMenu = true;
            Exit = true;

        } // $ ######### PLAY GAME ########
        else if (strcmpi(menu, "PLAY") == 0) {
            // $ Kamus Lokal : Start Game
            char load;
            char command[100];
            Stack GameState;
            Player PlayerOne, PlayerTwo;
			Bangunan DataBangunan;
            TabColor Pallete;
            MATRIKS MapBlueprint;
            Graph RelasiBan;
            int Baris, Kolom, CountBan, Turn;
            CreatePlayer(&PlayerOne);
            CreatePlayer(&PlayerTwo);
            MakeBukuWarna(&Pallete);

            // todo Load Game
            printf("Do you want to load a previous game? ");
            do {
                printf("Y/N\n");
                scanf(" %c", &load);
                if (load == 'Y') {
                    LoadFile(GameState);
                } else if (load == 'N') {
                    //LoadData();
                    MakeEmptyBangunan(&DataBangunan, 100);
                    printf("Choose building color for Player 1! \n");
                    SetPlayerWarna(&PlayerOne,&Pallete);
                    printf("Choose building color for Player 2! \n");
                    SetPlayerWarna(&PlayerTwo,&Pallete);
                    // * CONFIGURE
                    STARTKATA();
                    Baris = KataToInt(CKata);
                    ADVKATA();
                    Kolom = KataToInt(CKata);
                    ADVKATA();
                    CountBan = KataToInt(CKata);
                    ADVKATA();
                    DataBangunan = KataToBangunan(CountBan);
                    MapBlueprint = KataToMatriks(Baris, Kolom, DataBangunan);
                    RelasiBan = KataToGraph(CountBan);
                    // * Bangunan pertama pemain
                    InsVPrio(&ListBan(PlayerOne),1);
                    InsVPrio(&ListBan(PlayerTwo),2);

                    // * AKHIRNYA MULAI
                    Turn = 1;
                    StartTurn(&GameState,PlayerOne,PlayerTwo,Turn,DataBangunan);
                }
            } while (load != 'Y' && load != 'N');

            // todo maen game
            // * Countdown
            /*
            clrscrn();
            printf("              Starting game in...\n\n");
            sleep(1);
            printf("              3...\n\n");
            sleep(1);
            printf("                     2...\n\n");
            sleep(1);
            printf("                             1...\n");
            sleep(1);
            */
            clrscrn();
            getchar();
            do {
                // $$ Inisiasi Turn
                // $ Kamus Turn
                EndTurn = false;
                Player *CurrP;
                Player *EnemyP;
                Queue *Qcurr;
                Queue *Qenemy;
                List *Lcurr;
                Bangunan *StateDataB;
                if (TurnInfo(Curr(GameState)) == 1) {
                    CurrP = &P1Info(Curr(GameState));
                    EnemyP = &P2Info(Curr(GameState));
                } else {
                    CurrP = &P2Info(Curr(GameState));
                    EnemyP = &P1Info(Curr(GameState));
                }
                Qcurr = &Skill(*CurrP);
                Qenemy = &Skill(*EnemyP);
                Lcurr = &ListBan(*CurrP);
                StateDataB = &DataB(Curr(GameState));
                TambahAllTentara(*Lcurr, StateDataB);
                do {
                    if (TurnInfo(Curr(GameState)) == 1) {
                        CurrP = &P1Info(Curr(GameState));
                        EnemyP = &P2Info(Curr(GameState));
                    } else {
                        CurrP = &P2Info(Curr(GameState));
                        EnemyP = &P1Info(Curr(GameState));
                    }
                    Qcurr = &Skill(*CurrP);
                    Qenemy = &Skill(*EnemyP);
                    Lcurr = &ListBan(*CurrP);
                    StateDataB = &DataB(Curr(GameState));
                    // $ Display Status
                    PrintMap(MapBlueprint, *StateDataB, PlayerOne, PlayerTwo);
                    PrintCurr(GameState);
                    
                    Command();
                    int idxCommand = 0;
                    do {
                        scanf("%c", command + idxCommand);
                    } while (command[idxCommand++] != '\n');
                    command[--idxCommand] = '\0';
					printf("\n");


                        // $ ######### ATTACK ########
                    if (strcmpi(command,"ATTACK") == 0) {
                        Push(&GameState,Curr(GameState));
                        ATTACK(&GameState,StateDataB, RelasiBan);
                        getchar();

                    }   // $ ######### LEVEL_UP ########
                    else if (strcmpi(command, "LEVEL_UP") == 0) {
                        PrintTop(InfoTop(GameState));
                        Push(&GameState,Curr(GameState));
                        printf("==============INFOTOP BEFORE================\n");
                        PrintTop(InfoTop(GameState));
                    	LEVEL_UP(&GameState);
                        printf("==============INFOTOP AFTER================\n");
                        PrintTop(InfoTop(GameState));
                        getchar();

                    }   // $ ######### SKILL ########
                    else if (strcmpi(command, "SKILL") == 0) {
                        Push(&GameState,Curr(GameState));
                    	SKILL(&GameState,StateDataB);

                    }   // $ ######### MOVE ########
                    else if (strcmpi(command, "MOVE") == 0) {
                        Push(&GameState,Curr(GameState));
						MOVE(&GameState,StateDataB, RelasiBan);
                        getchar();


                    }   // $ ######### UNDO ########
                    else if (strcmpi(command, "UNDO") == 0) {
						UNDO(&GameState);

                    }   // $ ######### END_TURN ########
                    else if (strcmpi(command, "END_TURN") == 0) {
						EndTurn = true;
                        // ! Detector Skill Instant Reinforcement
                        CheckGetIR(CurrP,StateDataB);

                    }   // $ ######### SAVE ########
                    else if (strcmpi(command, "SAVE") == 0) {
						SAVE(&GameState);
                        getchar();

                    }   // $ ######### EXIT ########
                    else if (strcmpi(command, "EXIT") == 0) {
						ExitMenu = EXIT(&GameState);
						EndTurn = ExitMenu;
                        getchar();

					}
					else Invalid();
					printf("\n");

            	} while (!EndTurn);
                if (!ExitMenu) {
					ChangeTurn(&GameState,StateDataB);
					EndTurn = false;
				}
            } while (!IsLose(PlayerOne) && !IsLose(PlayerTwo) && !ExitMenu);
            if (IsLose(PlayerTwo)) {
                P1Wins();
            } else if (IsLose(PlayerOne)) {
                P2Wins();
			}

        } else {
            Invalid();
            getchar();
        }

    } while (!ExitMenu);
    ExitMenu = false;
} while (!Exit);
return 0;
}
