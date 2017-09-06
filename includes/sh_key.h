#ifndef SH_KEY_H
# define SH_KEY_H

# define K_TAB 9
# define K_ESC 27
# define K_DEL_L 127
# define K_DEL_R 2142190631
# define K_UP 4316599
# define K_DOWN 4382648
# define K_RIGHT 4448697
# define K_LEFT 4514746
# define K_HOME 4778942
# define K_END 4646844
# define K_P_UP 2142322729
# define K_P_DOWN 2142388778
# define K_C_UP 73107283740760
# define K_C_DOWN 74228438633817
# define K_C_RIGHT 75349593526874
# define K_C_LEFT 76470748419931
# define K_S_UP 73094196329557
# define K_S_DOWN 74215351222614
# define K_S_RIGHT 75336506115671
# define K_S_LEFT 76457661008728
# define K_CS_UP 73111646211161
# define K_CS_DOWN 74232801104218
# define K_CS_RIGHT 75353955997275
# define K_CS_LEFT 76475110890332

# ifdef __linux__
#  define K_CUT 30867
# else
#  define K_CUT -1
# endif

# ifdef __linux__
#  define K_COPY 25470
# else
#  define K_COPY -1
# endif

# ifdef __linux__
#  define K_PASTE 30353
# else
#  define K_PASTE -1
# endif

#endif
