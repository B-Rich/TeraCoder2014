//
//  source.c
//  TeraCoder2014
//
//  Created by kuroneko on 2014/12/19.
//  Copyright (c) 2014年 kuroneko. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * この問題で必要となる情報の構造体
 */
struct{
	int width; // 入力 X : 盤面の横の長さ
	int height; // 入力 Y : 盤面の縦の長さ
	char **board; // 白黒ゲームの盤面
} typedef DataSet;

/**
 * データ読み込み時に使用するバッファ
 */
char buffer[1024];

/**
 * 入力データをバッファに書き込む
 */
void input( void );

/**
 * 初期設定を行う
 * @return
 *	初期設定済みのデータセット
 */
DataSet* initialize();

/**
 * 終了処理
 * @param data
 *	終了処理を行うデータセット
 */
void finish( DataSet *data );

/**
 * 次のターンの処理を行う
 * @param data
 *	処理結果を更新するデータセット
 */
void next( DataSet *data );

/**
 * 盤面の色を塗る処理を行う
 * @param data
 *	盤面情報を保持しているデータセット
 */
void draw( DataSet *data , char color );

/**
 * 結果を表示する
 * @param data
 *	結果を表示するためのデータセット
 */
void result( DataSet *data );

int main( void ){
	input();
	int number = atoi( buffer );
	while( number-- ){
		DataSet *data = initialize();
		input();
		int n = atoi( buffer );
		while( n-- ){
			next( data );
		}
		result( data );
		finish( data );
	}
	return EXIT_SUCCESS;
}

void input( void ){
	if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	return;
}

DataSet* initialize( void ){
	DataSet *data = ( DataSet* ) malloc( sizeof( DataSet ) );
	input();
	char *string = strtok( buffer , " " );
	data->width = atoi( string );
	string = strtok( NULL , " " );
	data->height = atoi( string );
	char **board = data->board = ( char ** ) malloc( sizeof( char * ) * data->height );
	int allocation = data->width + 1;
	int index = data->height;
	while( index-- ){
		*board = ( char * ) malloc( sizeof( char ) * allocation );
		memset( *board , '.' , data->width );
		( *board++ )[allocation-1] = '\0';
	}
	return data;
}

void finish( DataSet *data ){
	if( data != NULL ){
		if( data->board != NULL ){
			char **board = data->board;
			int index = data->height;
			while( index-- ){
				if( *board != NULL ){
					free( *board );
					*board = NULL;
				}
				board++;
			}
			free( data->board );
			data->board = NULL;
		}
		free( data );
	}
	return;
}

void next( DataSet *data ){
	draw( data , 'W' );
	draw( data , 'B' );
	return;
}

void draw( DataSet *data , char color ){
	input();
	char *string = strtok( buffer , " " );
	int number = atoi( string ) - 1;
	string = strtok( NULL , " " );
	bool flag = atoi( string );
	int index;
	if( flag ){
		index = data->height;
		char **board = data->board;
		while( index-- ){
			( *board++ )[number] = color;
		}
	}
	else{
		index = data->width;
		char *board = data->board[number];
		while( index-- ){
			*board++ = color;
		}
	}
	return;
}

void result( DataSet *data ){
	char **board = data->board;
	int index = data->height;
	while( index-- ){
		fputs( *board++ , stdout );
		fputc( '\n' , stdout );
	}
	fputs( "#\n" , stdout );
	return;
}
