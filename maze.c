/*	Maze Generator
 *  Copyright (C) 2020 Samuele Girgenti
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	     --  CONTACTS --
 *  Email:      samuele.girgenti458@gmail.com
 *  Github:     https://github.com/Samuele458
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DIR 4
#define VALUES 19
#define SPACE 32

//config parameters
#define SIZE 121
#define WALL 'O'
#define WALK '.'
#define SPEED 10000

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#endif

#ifdef linux
#define CLEAR_SCREEN "clear"
#endif

void print_array( char const array[][ SIZE ] );
void mazeGenerator( char array[][ SIZE ] );
void mazeTravers( char array[][ SIZE ], size_t column, size_t row , unsigned int direction );
void push_stack( const size_t column, const size_t row, size_t cStack[], size_t rStack[], size_t *index );
void pop_stack( const size_t column, const size_t row, size_t cStack[], size_t rStack[], size_t *index );
int setStart( char array[][ SIZE ] );
void setEnd( char array[][ SIZE ] );

int main( void ) {
    char labyrinth[ SIZE ][ SIZE ] = { 0 };
    size_t start;
    srand( time ( NULL ) );

    //generating maze
    mazeGenerator( labyrinth );
    setEnd( labyrinth);
    start = setStart( labyrinth );

    //solving maze
    labyrinth[ start ][ 0 ] = WALK;
    mazeTravers( labyrinth, start, 0, 1 );
}

void print_array( char const array[][ SIZE ] ) {
    size_t row;
    size_t column;
    for ( column = 0; column < SIZE; ++column ) {
        for ( row = 0; row < SIZE; ++row ) {
            printf( " %c", array[ column ][ row ] );
        }
        puts( "" );
    }
}

void mazeGenerator( char array[][ SIZE ] ) {
    void setValues( size_t values[][ VALUES ], size_t column, size_t row );


    size_t column;
    size_t row;
    size_t index = 0;
    size_t *indexPtr = &index;
    size_t cStack[ SIZE * SIZE ] = { 0 };
    size_t rStack[ SIZE * SIZE ] = { 0 };
    unsigned int direction;
    int cont = 4;
    int array_dir[ 4 ] = { 0 };
    size_t values[ DIR ][ VALUES ] = { 0 };
    size_t x;
    int set = 0;


    for ( column = 0; column < SIZE; ++column ) {
        for ( row = 0; row < SIZE; ++row ) {
            array[ column ][ row ] = WALL;
        }
    }
    column = 3;
    row = 5;
    array[ column ][ row ] = SPACE;

    push_stack( column, row, cStack, rStack, indexPtr );

    srand( time( NULL ) );
    for ( ; ; ) {
        for ( ; ; ) {
            while( cont > 0 ) {
                set = 0;
                direction = ( 1 + rand() % DIR ) - 1;
                if ( array_dir[ direction ] == 0 ) {
                    array_dir[ direction ] = 1;
                    --cont;

                    setValues( values, column, row );
                    for ( x = 0; x < DIR; ++x ) {
                        if ( direction == x && array[values[x][0]][values[x][1]] !=SPACE && array[values[x][2]][values[x][3]] !=SPACE && array[values[x][4]][values[x][5]] !=SPACE && array[values[x][6]][values[x][7]] !=SPACE && array[values[x][8]][values[x][9]] !=SPACE && array[values[x][10]][values[x][11]] !=SPACE && array[values[x][12]][values[x][13]] !=SPACE && array[values[x][14]][values[x][15]] !=SPACE && array[values[x][16]][values[x][17]] !=SPACE && values[x][18] ) {
                            column = values[ x ][ 0 ];
                            row = values[ x ][ 1 ];
                            array[ column ][ row ] = SPACE;
                            setValues( values, column, row );
                            column = values[ x ][ 0 ];
                            row = values[ x ][ 1 ];
                            array[ column ][ row ] = SPACE;
                            push_stack( column, row, cStack, rStack, indexPtr );
                            cont = 4;
                            set = 1;
                            break;
                        }
                    }
                    if ( set == 1 ) {
                        break;
                    }
                }

            }
            if (cont==0)
                break;

            array_dir[ 0 ] = 0;
            array_dir[ 1 ] = 0;
            array_dir[ 2 ] = 0;
            array_dir[ 3 ] = 0;
        }
        if ( index >= 1 ) {
            pop_stack( column, row, cStack, rStack, indexPtr );
            column = cStack[ index ];
            row = rStack[ index ];
            array_dir[ 0 ] = 0;
            array_dir[ 1 ] = 0;
            array_dir[ 2 ] = 0;
            array_dir[ 3 ] = 0;
            cont = 4;
        } else {
            break;
        }
    }
}

int setStart( char array[][ SIZE ] ) {
    size_t random = 0;
    random = 1 + rand() % ( SIZE - 2 );
    while ( array[ random ][ 1 ] != SPACE ) {
        random = 1 + rand() % ( SIZE - 2 );
    }
    array[ random ][ 0 ] = SPACE;
    return random;
}

void setEnd( char array[][ SIZE ] ) {
    size_t random = 0;
    random = 1 + rand() % ( SIZE - 2 );
    while ( array[ random ][ SIZE - 2 ] != SPACE ) {
        random = 1 + rand() % ( SIZE - 2 );
    }
    array[ random ][ SIZE - 1 ] = SPACE;
}

void setValues( size_t values[][ VALUES ], size_t column, size_t row ) {
    size_t Table[ DIR ][ VALUES ] = {  { column, row + 1, column, row + 2, column, row + 3, column - 1, row + 1, column + 1, row + 1, column + 1, row + 2, column - 1, row + 2, column - 1, row + 3, column + 1, row + 3, row < ( SIZE - 2 ) },
                                 { column, row - 1, column, row - 2, column, row - 3, column - 1, row - 1, column - 1, row - 2, column - 1, row - 3, column + 1, row - 1, column + 1, row - 2, column + 1, row - 3, row > 1 },
                                 { column - 1, row, column - 2, row, column - 3, row, column - 1, row + 1, column - 2, row + 1, column - 3, row + 1, column - 1, row - 1, column - 2, row - 1, column - 3, row - 1, column > 1 },
                                 { column + 1, row, column + 2, row, column + 3, row, column + 1, row + 1, column + 2, row + 1, column + 3, row + 1, column + 1, row - 1, column + 2, row - 1, column + 3, row - 1, column < ( SIZE - 2 ) } };
    size_t x, y;
    for ( x = 0; x < DIR; ++x ) {
        for ( y = 0; y < VALUES; ++y ) {
            values[ x ][ y ] = Table[ x ][ y ];
        }
    }
}

void mazeTravers( char array[][ SIZE ], size_t column, size_t row, unsigned int direction ) {
    int checkDirection( const char array[][ SIZE ], size_t *column, size_t *row, const unsigned int direction );
    void changeDirection( unsigned int *direction, const unsigned int mode );
    size_t *columnPtr = &column;
    size_t *rowPtr = &row;
    unsigned int *dirPtr = &direction;
    if( row == SIZE - 1 ) {
        array[ column ][ row ] = WALK;
    } else {
        if ( checkDirection( array, columnPtr, rowPtr, direction ) == 1 ) {
            array[ column ][ row ] = WALK;
            usleep( SPEED );
            system( CLEAR_SCREEN );
            print_array( array );
            puts( "" );
            changeDirection( dirPtr, 2 );
        } else {
            changeDirection( dirPtr, 1 );
        }
        mazeTravers( array, column, row, direction );

    }
}

int checkDirection( const char array[][ SIZE], size_t *column, size_t *row, const unsigned int direction ) {
    size_t column_copy;         
    size_t row_copy;            
    size_t set_dir_c[ 4 ] = { *column, *column + 1, *column, *column - 1 }; 
    size_t set_dir_r[ 4 ] = { *row - 1, *row, *row + 1, *row }; 
    int x;  
    column_copy = *column;
    row_copy = *row;


    for ( x = 0; x < 4; ++x ) {         
        if ( direction == x ) {
            *column = set_dir_c[ x ];
            *row = set_dir_r[ x ];
            if ( array[ *column ][ *row ] == SPACE || array[ *column ][ *row ] == WALK ) {
                return 1;
            } else {
                *column = column_copy;
                *row = row_copy;
            }
        }
    }
    return 0;
}

void changeDirection( unsigned int *direction, const unsigned int mode ) { 
    if ( mode == 1 ) {
        *direction += 1;
        if ( *direction == 4 ) {
            *direction = 0;
        }
    } else if ( mode == 2 ) {
        if ( *direction == 0 ) {
            *direction = 3;
        } else {
            *direction -= 1;
        }
    }
}

void push_stack( const size_t column, const size_t row, size_t cStack[], size_t rStack[], size_t *index ) {
    cStack[ *index ] = column;
    rStack[ *index ] = row;
    *index += 1;
}

void pop_stack( const size_t column, const size_t row, size_t cStack[], size_t rStack[], size_t *index ) {
    cStack[ *index ] = column;
    rStack[ *index ] = row;
    *index -= 1;
}





