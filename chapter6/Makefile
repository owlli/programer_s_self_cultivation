
CC = gcc

all: SectionMapping MaxMallocSize

SectionMapping: SectionMapping.c
	$(CC) -static $< -o SectionMapping.elf

MaxMallocSize: MaxMallocSize.c
	$(CC) $< -o $@

clean:
	rm -rf SectionMapping.elf MaxMallocSize
