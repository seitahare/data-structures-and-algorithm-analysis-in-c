#include <stdio.h>

typedef unsigned int INDEX;

INDEX hash(char *key, unsigned int H_SIZE)
{

  unsigned int hash_val = 0;

  while (*key != '\0') {
    hash_val += *key++;
  }

  return hash_val % H_SIZE;
}

INDEX hash2(char *key, unsigned int H_SIZE)
{
  unsigned int hash_val = 0;

  for (int i = 0; key[i] != '\0'; i++) {
    hash_val = hash_val * 32 + (unsigned char)key[i];
  }

  return hash_val % H_SIZE;
}

int main(void)
{

  printf("hash(abc) = %u\n", hash("abc", 11));
  printf("hash(bca) = %u\n", hash("bca", 11));

  return 0;
}


