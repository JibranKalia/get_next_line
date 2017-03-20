CFLAGS="-Wall -Wextra -Werror -I libft/includes"

clang $CFLAGS -o get_next_line.o -c get_next_line.c
clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
clang -Wall -Wextra -Werror -I libft/includes -o alloc_wrap.o -c alloc_wrap.c
#clang -o test_gnl alloc_wrap.o main.o get_next_line.o -I libft/includes -L libft/ -lft
clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
rm *.o
