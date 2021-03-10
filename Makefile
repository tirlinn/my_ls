.PHONY: all cd cf cc lmy lls clean

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

TARGET = my_ls

all: cd cf $(TARGET) lmy lls lmy1 lls1 lmy2 lls2 lmy5 lls5 lmy6 lls6 lmy7 lls7 lmy8 lls8 lmy9 lls9 lmy10 lls10 clean

cd:
	mkdir ex00 ex01

cf: 
	touch ex00/00 ex00/01.txt ex01/00 ex01/01.txt

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c $(CFLAGS)

lmy: $(TARGET)
	./$(TARGET)

lls: 
	ls

lmy1: $(TARGET)
	./$(TARGET) .

lls1: 
	ls .

lmy2: $(TARGET)
	./$(TARGET) /tmp/

lls2: 
	ls /tmp/

lmy3: $(TARGET)
	./$(TARGET) dir_not_exist/

lls3: 
	ls dir_not_exist/

lmy4: $(TARGET)
	./$(TARGET) file_not_exist

lls4: 
	ls file_not_exist

lmy5: $(TARGET)
	./$(TARGET) ex00 ex01

lls5: 
	ls ex00 ex01

lmy6: $(TARGET)
	./$(TARGET) -t

lls6: 
	ls -t

lmy7: $(TARGET)
	./$(TARGET) -at

lls7: 
	ls -at

lmy8: $(TARGET)
	./$(TARGET) -a

lls8: 
	ls -a

lmy9: $(TARGET)
	./$(TARGET) -t -a

lls9: 
	ls -t -a

lmy10: $(TARGET)
	./$(TARGET) -a -t

lls10: 
	ls -a -t

clean: 
	rm -r ex00 ex01 $(TARGET)