#include "font.h"

int kerning = 1;
int fontWidth = 5;

int fontAlphabet [26][5][5] = {
	 // A
	{{0, 1, 1, 1, 0},
	 {1, 0, 0, 0, 1},
 	 {1, 1, 1, 1, 1},
	 {1, 0, 0, 0, 1},
	 {1, 0, 0, 0, 1}},
	 // B
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
  	 {1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
 	 {1, 1, 1, 1, 0}},
	 // C
 	{{0, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 0},
  	 {1, 0, 0, 0, 0},
 	 {1, 0, 0, 0, 0},
 	 {0, 1, 1, 1, 1}},
	 // D
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
 	 {1, 1, 1, 1, 0}},
	 // E
 	{{1, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 0},
  	 {1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 0},
 	 {1, 1, 1, 1, 1}},
	 // F
 	{{1, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 0},
  	 {1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 0},
 	 {1, 0, 0, 0, 0}},
	 // G
 	{{0, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 0},
  	 {1, 0, 1, 1, 1},
 	 {1, 0, 0, 0, 1},
 	 {0, 1, 1, 1, 1}},
	 // H
 	{{1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
  	 {1, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1}},
	 // I
 	{{0, 1, 1, 1, 0},
 	 {0, 0, 1, 0, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0},
 	 {0, 1, 1, 1, 0}},
	 // J
 	{{0, 0, 1, 1, 1},
 	 {0, 0, 0, 0, 1},
  	 {0, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
 	 {0, 1, 1, 1, 0}},
	 // K
 	{{1, 0, 0, 1, 0},
 	 {1, 0, 1, 0, 0},
  	 {1, 1, 0, 0, 0},
 	 {1, 0, 1, 0, 0},
 	 {1, 0, 0, 1, 0}},
	 // L
 	{{1, 0, 0, 0, 0},
 	 {1, 0, 0, 0, 0},
  	 {1, 0, 0, 0, 0},
 	 {1, 0, 0, 0, 0},
 	 {1, 1, 1, 1, 0}},
	 // M
 	{{1, 0, 0, 0, 1},
 	 {1, 1, 0, 1, 1},
  	 {1, 0, 1, 0, 1},
 	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1}},
	 // N
 	{{1, 0, 0, 0, 1},
 	 {1, 1, 0, 0, 1},
  	 {1, 0, 1, 0, 1},
 	 {1, 0, 0, 1, 1},
 	 {1, 0, 0, 0, 1}},
	 // O
 	{{0, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
 	 {0, 1, 1, 1, 0}},
	 // P
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
  	 {1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 0},
 	 {1, 0, 0, 0, 0}},
	 // Q
 	{{0, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 1, 0, 1},
 	 {1, 0, 0, 1, 0},
 	 {0, 1, 1, 0, 1}},
	 // R
 	{{1, 1, 1, 0, 0},
 	 {1, 0, 0, 1, 0},
  	 {1, 1, 1, 0, 0},
 	 {1, 0, 1, 0, 0},
 	 {1, 0, 0, 1, 0}},
	 // S
 	{{0, 1, 1, 1, 1},
 	 {1, 0, 0, 0, 0},
  	 {0, 1, 1, 1, 0},
 	 {0, 0, 0, 0, 1},
 	 {1, 1, 1, 1, 0}},
	 // T
 	{{1, 1, 1, 1, 1},
 	 {0, 0, 1, 0, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0}},
	 // U
 	{{1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
 	 {0, 1, 1, 1, 0}},
	 // V
 	{{1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 0, 0, 1},
 	 {0, 1, 0, 1, 0},
 	 {0, 0, 1, 0, 0}},
	 // W
 	{{1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
  	 {1, 0, 1, 0, 1},
 	 {1, 0, 1, 0, 1},
 	 {0, 1, 0, 1, 0}},
	 // X
 	{{1, 0, 0, 0, 1},
 	 {0, 1, 0, 1, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 1, 0, 1, 0},
 	 {1, 0, 0, 0, 1}},
	 // Y
 	{{1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
  	 {1, 1, 1, 1, 1},
 	 {0, 0, 0, 0, 1},
 	 {1, 1, 1, 1, 0}},
	 // Z
 	{{1, 1, 1, 1, 1},
 	 {0, 0, 0, 1, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 1, 0, 0, 0},
 	 {1, 1, 1, 1, 1}}
};

int fontNumbers [10][5][5] = {
	 // 0
	{{0, 1, 1, 1, 0},
	 {1, 0, 0, 0, 1},
 	 {1, 0, 0, 0, 1},
	 {1, 0, 0, 0, 1},
	 {0, 1, 1, 1, 0}},
	 // 1
 	{{0, 1, 1, 0, 0},
 	 {0, 0, 1, 0, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0}},
	 // 2
 	{{0, 1, 1, 0, 0},
 	 {1, 0, 0, 1, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 1, 0, 0, 0},
 	 {1, 1, 1, 1, 0}},
	 // 3
 	{{1, 1, 1, 0, 0},
 	 {0, 0, 0, 1, 0},
  	 {0, 1, 1, 1, 0},
 	 {0, 0, 0, 1, 0},
 	 {1, 1, 1, 0, 0}},
	 // 4
 	{{1, 0, 1, 0, 0},
 	 {1, 0, 1, 0, 0},
  	 {1, 1, 1, 1, 0},
 	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0}},
	 // 5
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 0},
  	 {1, 1, 1, 0, 0},
 	 {0, 0, 0, 1, 0},
 	 {1, 1, 1, 0, 0}},
	 // 6
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 0, 0},
  	 {1, 1, 1, 1, 0},
 	 {1, 0, 0, 1, 0},
 	 {1, 1, 1, 1, 0}},
	 // 7
 	{{1, 1, 1, 1, 0},
 	 {0, 0, 0, 1, 0},
  	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0},
 	 {0, 0, 1, 0, 0}},
	 // 8
 	{{0, 1, 1, 0, 0},
 	 {1, 0, 0, 1, 0},
  	 {0, 1, 1, 0, 0},
 	 {1, 0, 0, 1, 0},
 	 {0, 1, 1, 0, 0}},
	 // 9
 	{{1, 1, 1, 1, 0},
 	 {1, 0, 0, 1, 0},
  	 {1, 1, 1, 1, 0},
 	 {0, 0, 0, 1, 0},
 	 {0, 0, 0, 1, 0}}
};

int fontPERIOD [5][5] = {
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0}
};

int fontCOLON [5][5] = {
	{0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0}
};

int fontHYPHEN [5][5] = {
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
};

int fontSLASH [5][5] = {
	{0, 0, 0, 0, 1},
	{0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0}
};
