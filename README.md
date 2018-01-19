# An optimization bug of Android NDK

## Software Version:

Host Platform: Ubuntu 16.04, 4.4.0-109-generic, x86_64 GNU/Linux<br />
Gradle Version: 4.1<br />
Android Plugin Version: 3.0.1<br />
Android SDK Build-Tools Version: 27.0.3<br />
NDK Version: 16.1.4479499<br />
CMake Version: 3.6.0-rc2<br />
Clang++ Version: Android clang version 5.0.300080  (based on LLVM 5.0.300080)


## Expected Output:
```
W/test: BEGIN
W/test: END
```

### When Building with "-O2" or "-O3"
```
W/test: BEGIN
E/test: ERROR: s.a = 255
```

### When Building with "-O1" or "-O0"
```
W/test: BEGIN
W/test: END
```

## Details:

See code:
```
/** A modified copy of the libusb function usbi_parse_descriptor
 *  https://github.com/libusb/libusb/blob/84209b4fb54ebc62f5a60f0122bddef3ebd97d0a/libusb/descriptor.c#L45
 *
 *
 * @param source         the source to copy the data
 * @param descriptor     how to copy the data. a string.
 *                       e.g. "bbw" -- reads two bytes and a word to dest
 * @param dest           the destination to copy the data to
 * @param host_endian    the endian
 * @return               bytes copied
 */
int usbi_parse_descriptor(const unsigned char *source, const char *descriptor,
                          void *dest, int host_endian)
{
  const unsigned char *sp = source;
  unsigned char *dp = (unsigned char *)dest;
  uint16_t w;
  const char *cp;
  uint32_t d;
  for (cp = descriptor; *cp; cp++) {
    switch (*cp) {
      case 'b':	/* 8-bit byte */
        *dp++ = *sp++;
        break;
      case 'u':	/* 16 byte UUID */
        memcpy(dp, sp, 16);
        sp += 16;
        dp += 16;
        break;
    }
  }

  return (int) (sp - source);
}

struct Struct {
  unsigned char a;
  unsigned char b;
};

int tmain() {
  __android_log_print(ANDROID_LOG_WARN, "test", "BEGIN");
  struct Struct s;
  unsigned char buffer[] = {9, 4};
  int size = sizeof(buffer);
  s.a = 0xff;
  while (size >= 2) {
    usbi_parse_descriptor(buffer, "bb", &s, 0);
    if (s.a != 9) {
      __android_log_print(ANDROID_LOG_ERROR, "test", "ERROR: s.a = %d", s.a);
      return -1;
    } else {
      size -= 2;
    }
  }
  __android_log_print(ANDROID_LOG_WARN, "test", "END");
  return 0;
}
```
