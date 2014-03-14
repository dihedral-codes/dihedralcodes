#include <stdio.h>
#include "dihcodes.h"


void re_check_ds( unsigned long long stem , int my_one_num , int tot_num_ones , int num_zeros_used , int num_zeros_fir_sec ) ;

int  best_min_dist_d( unsigned long long d ) ;
int re_best_min_dist_d( unsigned long long d , unsigned long long stem , int my_one_num , int tot_num_ones , int num_zeros_used , int num_zeros_fir_sec ) ;

int check_comb( unsigned long long d , unsigned long long rowcomb ) ;

int main( int argc , char *argv[] ) {

	int poss_wt , sec_ones_pos ;
	
	for ( poss_wt = D - 1 ; poss_wt < K ; poss_wt += 4 )
		for ( sec_ones_pos = 1 ;
		      sec_ones_pos < K - sec_ones_pos - 1 - ( ( poss_wt - 2 ) * sec_ones_pos ) ;
		      sec_ones_pos++ )
			re_check_ds( ( 1 | ( ( ( unsigned long long ) 1 ) << sec_ones_pos ) ) , 3 , poss_wt , sec_ones_pos - 1 , sec_ones_pos - 1 ) ;


	return( 0 ) ;

}

void re_check_ds( unsigned long long stem , int my_one_num , int tot_num_ones , int num_zeros_used , int num_zeros_fir_sec ) {

	int my_position ;

	if ( my_one_num == tot_num_ones ) {

		for ( my_position = num_zeros_used + ( my_one_num - 1 ) + num_zeros_fir_sec ;
		      my_position < K - num_zeros_fir_sec - 1 ;
		      my_position++ )
			if ( unitary( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) )
				if ( best_min_dist_d( ( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) ) ) {

					bin_printf( ( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) ) ;
					printf( "\n" ) ;

				}


	} else {

		for ( my_position = num_zeros_used + ( my_one_num - 1 ) + num_zeros_fir_sec ;
		      my_position < K - num_zeros_fir_sec - ( ( tot_num_ones - my_one_num ) * ( num_zeros_fir_sec + 1 ) ) - 1 ;
		      my_position++ ) {

			re_check_ds(
				( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) ,
				( my_one_num + 1 ) ,
				tot_num_ones ,
				( my_position - my_one_num + 1 ) ,
				num_zeros_fir_sec
			) ;

		}


	}


}

int  best_min_dist_d( unsigned long long d ) {

	int poss_wt , sec_ones_pos ;

	for ( sec_ones_pos = 1 ; sec_ones_pos < ( K / 2 ) + 1 ; sec_ones_pos++ )
		if ( !check_comb( d , ( unsigned long long ) 1 | ( ( ( unsigned long long ) 1 ) << sec_ones_pos ) ) )
			return( 0 ) ;

	for ( poss_wt = 3 ; poss_wt < ( K + 1 ) ; poss_wt++ )
		for ( sec_ones_pos = 1 ;
		      sec_ones_pos < K - sec_ones_pos - 1 - ( ( poss_wt - 2 ) * sec_ones_pos ) - 1 ;
		      sec_ones_pos++ )
			if ( !re_best_min_dist_d( d ,  ( 1 | ( ( ( unsigned long long ) 1 ) << sec_ones_pos ) ) , 3 , poss_wt , sec_ones_pos - 1 , sec_ones_pos - 1 ) )
				return( 0 ) ;


	return( 1 ) ;

}

int re_best_min_dist_d( unsigned long long d , unsigned long long stem , int my_one_num , int tot_num_ones , int num_zeros_used , int num_zeros_fir_sec ) {

	int my_position ;

	if ( my_one_num == tot_num_ones ) {

		for ( my_position = num_zeros_used + ( my_one_num - 1 ) + num_zeros_fir_sec ;
		      my_position < K - num_zeros_fir_sec - 1 ;
		      my_position++ )
			if ( !check_comb( d , ( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) ) )
				return( 0 ) ;


	} else {

		for ( my_position = num_zeros_used + ( my_one_num - 1 ) + num_zeros_fir_sec ;
		      my_position < K - num_zeros_fir_sec - ( ( tot_num_ones - my_one_num ) * ( num_zeros_fir_sec + 1 ) ) - 1 ;
		      my_position++ )

			if ( !re_best_min_dist_d(
				d ,
				( stem | ( ( ( unsigned long long ) 1 ) << my_position ) ) ,
				( my_one_num + 1 ) ,
				tot_num_ones ,
				( my_position - my_one_num + 1 ) ,
				num_zeros_fir_sec
			) ) return( 0 ) ;

		


	}

	return( 1 ) ;


}

int check_comb( unsigned long long d , unsigned long long rowcomb ) {

	unsigned long long codeword = d ;
	int i ;

	for ( i = 1 ; i < K ; i++ ) 
		if ( rowcomb & ( ( ( unsigned long long ) 1 ) << i ) )
			( codeword ^= rowi( d , i ) ) ;


	if ( ( wt( codeword ) + wt( rowcomb ) ) < D ) return( 0 ) ;
	else                          return( 1 ) ;

}
