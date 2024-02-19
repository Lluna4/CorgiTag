#include "endian.h"
#include "utils.h"

enum NbtNodeType {
  End = 0x00,
  Byte = 0x01,
  Short = 0x02,
  Int = 0x03,
  Long = 0x04,
  Float = 0x05,
  Double = 0x06,
  ByteArray = 0x07,
  String = 0x08,
  List = 0x09,
  Compound = 0x0A,
  IntArray = 0x0B,
  LongArray = 0x0C
};

struct NbtByteArray{
  int len;
  int* data;
};

struct NbtString {
  unsigned short len;
  char* data;
};

struct NbtList {
  int type;
  int len;
  void* data;
};

struct NbtNode {
  int type;
  int is_named; //bool
  int name_len; //bool
  char* name;
  int data_len;
  void* data;
};

struct NbtNode nodes[1024];
int n = 0;

void parse(char *nbt)
{
  struct NbtNode new_node = {0};
  char *name;
  short name_len = 0;
  char *data;
  char *type = nbt;

  nbt++;
  name_len = read_short(nbt);
  nbt = nbt + sizeof(short);
  name = read_string(nbt, name_len);
  nbt = nbt + name_len;
  switch (*type)
  {
    case End:
      return;
    case Byte:
      data = (char *)malloc(1 * sizeof(char));
      data[0] = *nbt;
      new_node = (struct NbtNode){.type = Byte, .is_named = 1, .name_len = name_len,.name = name, .data_len = 1, .data = data};
      nbt = nbt + sizeof(char);
      break;
    case Short:
      data = (char *)malloc(sizeof(short) * sizeof(char));
      memcpy(data, nbt, sizeof(short));
      new_node = (struct NbtNode){.type = Short, .is_named = 1, .name_len = name_len,.name = name, .data_len = sizeof(short), .data = data};
      nbt = nbt + sizeof(short);
      break;
  }
  nodes[n] = new_node;
  n++;
  parse(nbt);
}