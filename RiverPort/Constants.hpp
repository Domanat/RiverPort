#ifndef CONST_H
#define CONST_H

#include <SFML/Graphics.hpp>

const int mapHeight = 21;
const int mapWidth = 50;
const int speed = 280;
const int jumpSpeed = 470;
const int cellSize = 32;
const int humanWidth = 32;
const int humanHeight = 32;
const int gravity = 1000;
const int animationSpeed = 7;
const int horizontal = 0;
const int vertical = 1;
const int windowWidth = 1280;
const int windowHeight = 720;
const int bulletWidth = 6;
const int bulletHeight = 2;
const int right = 1;
const int left = -1;

const sf::String map1[mapHeight] =
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                                               B",
	"BBBB      C                                     B",
	"B  CC     BBBBB               CC                B",
	"B BBBBB                            BBBBBBB     CB",
	"B                       BBBB          B        BB",
	"B              BBBB                   B         B",
	"BB                                    B         B",
	"B       BBBBBBBBB                           BBBBB",
	"BBB                   BB                        B",
	"B       CCCC          BB      C                 B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   BBBB   BBBB",
	"B                               BBC             B",
	"B  C              CC            BBBBB       BBBBB",
	"B BBB         BBBBBBBB          B               B",
	"B                                        BBBBBBBB",
	"B       BB            CC                BB   CC B",
	"BBBBB             BBBBBBBB             B        B",
	"B       BBBBB                                 BBB",
	"B          CC         C            CC           B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

const sf::String map2[mapHeight] =
{

	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                           C C          C C C  B",
	"BBBBB        C  C          BBBBB        BBBBBB  B",
	"B  CC      BBBBBBB            CC                B",
	"B BBBBB                   C                    CB",
	"B                    BBBBBBB         CC        BB",
	"B                                 BBBBBBBB      B",
	"BB       C C C C                            C   B",
	"BC      BBBBBBBBB       CCC                 BBBBB",
	"BBB                   BBBBBBBB                  B",
	"B     C    C                             C  C   B",
	"BBBBBBBBBBBBBBBBBBB                   BBBBBBBBBBB",
	"B                    C C C     C C C            B",
	"B                  BBBBBBBBBBBBBBBBBBB          B",
	"B   C C                             C        BBBB",
	"B  BBBBBBB                         BBBBB        B",
	"B                     CC                     CC B",
	"B                BBBBBBBBB             BBBBBBBBBB",
	"B       BBBBB                                   B",
	"B          CC         C            CC           B",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};
#endif