//
//  source.c
//  TeraCoder2014
//
//  Created by kuroneko on 2014/11/23.
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
	int x; // 入力 X : Base-X の X
	int n; // 入力 X から逆算出来る N : X = 2 ^ N
	int count; // 入力 C : 入力文字列数
	int result; // 結果出力文字数
	char *table; // 入力 T : テーブル
	char *plain; // 入力 S : 入力文字列
	char *cipher; // 結果文字列
} typedef DataSet;

/**
 * データセットの数を取得する
 * @return
 *	データセット数
 */
int getNumber( void );
/**
 * 符号化
 * @param data
 *	符号化を行うために必要な情報
 * @return
 *	符号化された文字列
 */
char *encode( DataSet *data );
//char *decode( DataSet *data );
/**
 * 初期設定
 * 入力値から初期値を設定する
 * @param data
 *	初期設定を行うデータセット
 */
void initialize( DataSet *data );
/**
 * 終了処理
 * @param data
 *	開放を行うデータセット
 */
void finish( DataSet *data );
/**
 * 入力 X から N を逆算する
 * @param x
 *	入力 X
 * @return
 *	逆算された N
 */
int getN( int x );

/**
 * 最大公約数を取得する
 * @param a
 *	一つ目の値
 * @param b
 *	二つ目の値
 * @return
 *	引数 a と b の最大公約数
 */
int gcd( int a , int b );

/**
 * 最小公倍数を取得する
 * @param a
 *	一つ目の値
 * @param b
 *	二つ目の値
 * @return
 *	引数 a と b の最小公約数
 */
int lcm( int a , int b );

/**
 * データ読み込み時のバッファ
 */
char buffer[1024];

int main( void ){
	int number = getNumber();
	while( number-- ){
		DataSet *data = ( DataSet * ) malloc( sizeof( DataSet ) );
		initialize( data );

		printf( "%s\n" , encode( data ) );

		finish( data );
	}
	return EXIT_SUCCESS;
}

int getNumber( void ){
	if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	return atoi( buffer );
}

char *encode( DataSet *data ){
		
	int mask = 0;
	for( int shift = 0 ; shift < data->n ; shift++ ){
		mask |= 0x80 >> shift;
	}
	for( int position = 0 ; position < data->result ; position++ ){
		int temporary = position * data->n;
		int index = temporary / 8;
		int table = data->x;
		if( index < data->count ){
			if( index == ( ( temporary + data->n - 1 ) / 8 ) ){
				temporary %= 8;
				table = ( ( 0xFF & data->plain[index] ) & ( mask >> temporary ) ) >> ( 8 - ( temporary + data->n ) );
			}
			else{
				temporary %= 8;
				int shift = data->n - ( 8 - temporary );
				table = ( ( 0xFF & data->plain[index] ) & ( mask >> temporary ) ) << shift;
				if( ++index < data->count ){
					table |= ( data->plain[index] & ( mask << ( 8 - temporary ) ) ) >> ( 8 - shift );
				}
			}
		}
		data->cipher[position] = data->table[table];
	}
	
	return data->cipher;
}

void initialize( DataSet *data ){
	char *string;
	if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	
	string = strtok( buffer , " " );
	data->x = atoi( string );
	data->n = getN( data->x );
	string = strtok( NULL , " " );
	data->count = atoi( string );
	
	int size = sizeof( char ) * ( data->x + 3 );
	data->table = ( char * ) malloc( size );
	if( fgets( data->table , size , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	size = sizeof( char ) * ( data->count + 2 );
	data->plain = ( char * ) malloc( size );
	if( fgets( data->plain , size , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	size_t result = data->count;
	result = ( ( result << 3 ) / data->n );
	int set = lcm( 8 , data->n ) / data->n;
	if( result % set ){
		result += set - ( ( result ) % set );
	}
	data->result = ( int ) result & 0xFFFFFFFF;
	data->cipher = ( char * ) malloc( sizeof( char ) * ( result + 1 ) );
	memset( data->cipher , '\0' , result + 1 );
	return;
}

// log 2
int getN( int x ){
	int mask = 0x1;
	for( int i = 0 ; i <= 8 ; i++ ){
		if( x == mask ){
			return i;
		}
		mask <<= 1;
	}
	return -1;
}

int gcd( int a , int b ){
	return b <= 0 ? a : gcd( b , a % b );
}

int lcm( int a , int b ){
	return a / gcd( a , b ) * b;
}

void finish( DataSet *data ){
	if( data != NULL ){
		if( data->table != NULL ){
			free( data->table );
			data->table = NULL;
		}
		if( data->plain != NULL ){
			free( data->plain );
			data->plain = NULL;
		}
		if( data->cipher != NULL ){
			free( data->cipher );
			data->cipher = NULL;
		}
		free( data );
	}
	return;
}
