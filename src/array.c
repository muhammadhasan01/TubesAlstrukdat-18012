/* NAMA / NIM :                           */
/* 1. Muhammad Hasan           / 13518012 */
/* 2. Anna Elvira Hartoyo      / 13518045 */
/* 3. Daniel Riyanto           / 13518075 */
/* 4. Faris Muhammad Kautsar   / 13518105 */
/* 5. Gregorius Jovan Kresnadi / 13518135 */

/* File body: array.c */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyBangunan (Bangunan * B, int maxel) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  printf("HAH\n");
  BI(*B) = (info_bangunan *) malloc ((maxel + 1)* sizeof(info_bangunan));
  MaxEl(*B) = maxel;
  Neff(*B) = 0;
}

void DealokasiBangunan(Bangunan *B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  free(BI(*B));
  MaxEl(*B) = 0;
  Neff(*B) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtBan (Bangunan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return Neff(B);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstBan (Bangunan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return IdxMin;
}

IdxType GetLastBan (Bangunan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return Neff(B);
}

int GetMaxTentara(Bangunan B, IdxType X) {
	if (Name(ElmtBan(B, X)) == 'C') {
		if (Level(ElmtBan(B, X)) == 1) {
		return MaxC1;

		} else if (Level(ElmtBan(B, X)) == 2) {
		return MaxC2;

		} else if (Level(ElmtBan(B, X)) == 3) {
		return MaxC3;

		} else /* Level(ElmtBan(B, X)) == 4 */ {
		return MaxC4;

		}
	} else if (Name(ElmtBan(B, X)) == 'T') {
		if (Level(ElmtBan(B, X)) == 1) {
		return MaxT1;

		} else if (Level(ElmtBan(B, X)) == 2) {
		return MaxT2;

		} else if (Level(ElmtBan(B, X)) == 3) {
		return MaxT3;

		} else /* Level(ElmtBan(B, X)) == 4 */ {
		return MaxT4;

		}
	} else if (Name(ElmtBan(B, X)) == 'F') {
		if (Level(ElmtBan(B, X)) == 1) {
		return MaxF1;

		} else if (Level(ElmtBan(B, X)) == 2) {
		return MaxF2;

		} else if (Level(ElmtBan(B, X)) == 3) {
		return MaxF3;

		} else /* Level(ElmtBan(B, X)) == 4 */ {
		return MaxF4;

		}
	} else /* Name(ElmtBan(B, X)) == 'V' */ {
		if (Level(ElmtBan(B, X)) == 1) {
		return MaxV1;

		} else if (Level(ElmtBan(B, X)) == 2) {
		return MaxV2;

		} else if (Level(ElmtBan(B, X)) == 3) {
		return MaxV3;

		} else /* Level(ElmtBan(B, X)) == 4 */ {
		return MaxV4;

		}
	}
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyBan (Bangunan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return (Neff(B) == 0);
}

/* *** Test tabel penuh *** */
boolean IsFullBan (Bangunan B) {
// ? Entah perlu fungsi ini gak ya?
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return (Neff(B) == MaxEl(B));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaBangunan (Bangunan * B) {
// Todo Menunggu yang kerjain Configure

}

//$ ******************** Tentara Attack ****************************/
boolean CheckAttackTentara (Bangunan B, IdxType X, int N) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return (Tentara(ElmtBan(B, X)) >= N);
}

void TentaraAttack (Bangunan * B, IdxType X, int N) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  Tentara(ElmtBan(*B, X)) -= N;

}

//$ ******************** Tentara Invaded **************************/
void InvadedShield (Bangunan * B, IdxType i, int N) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  if (Tentara(ElmtBan(*B, i)) > N * 3 / 4) {
    Tentara(ElmtBan(*B, i)) = Tentara(ElmtBan(*B, i)) - N * 3 / 4;
  } else /* Tentara(ElmtBan(*B, i)) <= N * 3 / 4 */ {
    Tentara(ElmtBan(*B, i)) = (-1) * (N - Tentara(ElmtBan(*B, i)) * 4 / 3);
  }
}

void TentaraInvaded (Bangunan * B, boolean Critical_Hit, boolean Attack_Up, boolean Shield, IdxType i, int N) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  if (Critical_Hit) {
    if (Tentara(ElmtBan(*B, i)) > 2 * N) {
      Tentara(ElmtBan(*B, i)) = Tentara(ElmtBan(*B, i)) - 2 * N;
    } else /* Tentara(ElmtBan(*B, i) <= 2 * N */ {
      if (Tentara(ElmtBan(*B, i)) % 2 == 1) {
        Tentara(ElmtBan(*B, i)) += 1;
      }

      Tentara(ElmtBan(*B, i)) = (-1) * (N - Tentara(ElmtBan(*B, i)) / 2);
    }

  } else /* !Critical_Hit */ {
    if (Attack_Up) {
      Tentara(ElmtBan(*B, i)) -= N;

    } else /* !Attack_Up */ {
      if (Shield) { 
        InvadedShield(B, i, N);

      } else /* !Shield */ { //* Skill apapun tidak aktif yang berhubungan dengan Attack
        if (Name(ElmtBan(*B, i)) == 'T') {
          InvadedShield(B, i, N);
        } else if (Name(ElmtBan(*B, i)) == 'F') {
          if ((Level(ElmtBan(*B, i)) == 3) || (Level(ElmtBan(*B, i)) == 4)) {
            InvadedShield(B, i, N);

          } else /* (Level(ElmtBan(*B, i)) == 1) || (Level(ElmtBan(*B, i)) == 2) */ {
            Tentara(ElmtBan(*B, i)) -= N;
          }

        } else /* (Name(ElmtBan(*B, i)) == 'C') || (Name(ElmtBan(*B, i)) == 'V') */ {
          Tentara(ElmtBan(*B, i)) -= N;
        }
      }
    }
  }
}

boolean CanCapture (Bangunan B, IdxType i) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return (Tentara(ElmtBan(B, i)) <= 0);
}

void TentaraAbsolute (Bangunan * B, IdxType X) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  Tentara(ElmtBan(*B, X)) = abs(Tentara(ElmtBan(*B, X)));
}

//$ ************************ Level-Up Bangunan ********************************/
boolean CheckLevelUp (Bangunan B, IdxType X) {
// ! Jika udah level 4 maka tidak bisa Level Up lagi
  /* KAMUS LOKAL */

  /* ALGORITMA */
  if (Name(ElmtBan(B, X)) == 'C') {
    if (Level(ElmtBan(B, X)) == 1) {
      return (Tentara(ElmtBan(B, X)) >= MaxC1/2);

    } else if (Level(ElmtBan(B, X)) == 2) {
      return (Tentara(ElmtBan(B, X)) >= MaxC2/2);

    } else if (Level(ElmtBan(B, X)) == 3) {
      return (Tentara(ElmtBan(B, X)) >= MaxC3/2);

    } else /* Level(ElmtBan(B, X)) == 4 */ {
      return false;

    }
  } else if (Name(ElmtBan(B, X)) == 'T') {
    if (Level(ElmtBan(B, X)) == 1) {
      return (Tentara(ElmtBan(B, X)) >= MaxT1/2);

    } else if (Level(ElmtBan(B, X)) == 2) {
      return (Tentara(ElmtBan(B, X)) >= MaxT2/2);

    } else if (Level(ElmtBan(B, X)) == 3) {
      return (Tentara(ElmtBan(B, X)) >= MaxT3/2);

    } else /* Level(ElmtBan(B, X)) == 4 */ {
      return false;

    }
  } else if (Name(ElmtBan(B, X)) == 'F') {
    if (Level(ElmtBan(B, X)) == 1) {
      return (Tentara(ElmtBan(B, X)) >= MaxF1/2);

    } else if (Level(ElmtBan(B, X)) == 2) {
      return (Tentara(ElmtBan(B, X)) >= MaxF2/2);

    } else if (Level(ElmtBan(B, X)) == 3) {
      return (Tentara(ElmtBan(B, X)) >= MaxF3/2);

    } else /* Level(ElmtBan(B, X)) == 4 */ {
      return false;

    }
  } else if (Name(ElmtBan(B, X)) == 'V') /* Name(ElmtBan(B, X)) == 'V' */ {
    if (Level(ElmtBan(B, X)) == 1) {
      return (Tentara(ElmtBan(B, X)) >= MaxV1/2);

    } else if (Level(ElmtBan(B, X)) == 2) {
      return (Tentara(ElmtBan(B, X)) >= MaxV2/2);

    } else if (Level(ElmtBan(B, X)) == 3) {
      return (Tentara(ElmtBan(B, X)) >= MaxV3/2);

    } else /* Level(ElmtBan(B, X)) == 4 */ {
      return false;

    }
  } else {return false;}
}

void LevelUp (Bangunan * B, IdxType X) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  Tentara(ElmtBan(*B, X)) = GetMaxTentara(*B,X)/2;
  Level(ElmtBan(*B, X)) += 1;
}
