#include <jni.h>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>

#include "libusb_definitions.h"

#define PACKAGE_NAME "com.polytpetech.libusb_bug"

#ifndef USE_CUSTOM_LOG
#define USE_CUSTOM_LOG
#define TAG PACKAGE_NAME
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__)
#endif

// the entrance function
int tmain();

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_polytopetech_libusb_1bug_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject /* this */) {
  std::string hello = "Hello from C++";
  tmain();
  return env->NewStringUTF(hello.c_str());
}

/** \ingroup libusb_misc
 * Error codes. Most libusb functions return 0 on success or one of these
 * codes on failure.
 * You can call libusb_error_name() to retrieve a string representation of an
 * error code or libusb_strerror() to get an end-user suitable description of
 * an error code.
 */
enum libusb_error {
  /** Success (no error) */
      LIBUSB_SUCCESS = 0,

  /** Input/output error */
      LIBUSB_ERROR_IO = -1,

  /** Invalid parameter */
      LIBUSB_ERROR_INVALID_PARAM = -2,

  /** Access denied (insufficient permissions) */
      LIBUSB_ERROR_ACCESS = -3,

  /** No such device (it may have been disconnected) */
      LIBUSB_ERROR_NO_DEVICE = -4,

  /** Entity not found */
      LIBUSB_ERROR_NOT_FOUND = -5,

  /** Resource busy */
      LIBUSB_ERROR_BUSY = -6,

  /** Operation timed out */
      LIBUSB_ERROR_TIMEOUT = -7,

  /** Overflow */
      LIBUSB_ERROR_OVERFLOW = -8,

  /** Pipe error */
      LIBUSB_ERROR_PIPE = -9,

  /** System call interrupted (perhaps due to signal) */
      LIBUSB_ERROR_INTERRUPTED = -10,

  /** Insufficient memory */
      LIBUSB_ERROR_NO_MEM = -11,

  /** Operation not supported or unimplemented on this platform */
      LIBUSB_ERROR_NOT_SUPPORTED = -12,

  /* NB: Remember to update LIBUSB_ERROR_COUNT below as well as the
     message strings in strerror.c when adding new error codes here. */

  /** Other error */
      LIBUSB_ERROR_OTHER = -99,
};

/* bus structures */

/* All standard descriptors have these 2 fields in common */
struct usb_descriptor_header {
  uint8_t bLength;
  uint8_t bDescriptorType;
};

/** \ingroup libusb_desc
 * A structure representing the standard USB endpoint descriptor. This
 * descriptor is documented in section 9.6.6 of the USB 3.0 specification.
 * All multiple-byte fields are represented in host-endian format.
 */
struct libusb_endpoint_descriptor {
  /** Size of this descriptor (in bytes) */
  uint8_t  bLength;

  /** Descriptor type. Will have value
   * \ref libusb_descriptor_type::LIBUSB_DT_ENDPOINT LIBUSB_DT_ENDPOINT in
   * this context. */
  uint8_t  bDescriptorType;

  /** The address of the endpoint described by this descriptor. Bits 0:3 are
   * the endpoint number. Bits 4:6 are reserved. Bit 7 indicates direction,
   * see \ref libusb_endpoint_direction.
   */
  uint8_t  bEndpointAddress;

  /** Attributes which apply to the endpoint when it is configured using
   * the bConfigurationValue. Bits 0:1 determine the transfer type and
   * correspond to \ref libusb_transfer_type. Bits 2:3 are only used for
   * isochronous endpoints and correspond to \ref libusb_iso_sync_type.
   * Bits 4:5 are also only used for isochronous endpoints and correspond to
   * \ref libusb_iso_usage_type. Bits 6:7 are reserved.
   */
  uint8_t  bmAttributes;

  /** Maximum packet size this endpoint is capable of sending/receiving. */
  uint16_t wMaxPacketSize;

  /** Interval for polling endpoint for data transfers. */
  uint8_t  bInterval;

  /** For audio devices only: the rate at which synchronization feedback
   * is provided. */
  uint8_t  bRefresh;

  /** For audio devices only: the address if the synch endpoint */
  uint8_t  bSynchAddress;

  /** Extra descriptors. If libusb encounters unknown endpoint descriptors,
   * it will store them here, should you wish to parse them. */
  const unsigned char *extra;

  /** Length of the extra descriptors, in bytes. */
  int extra_length;
};

/** \ingroup libusb_desc
 * A structure representing the standard USB interface descriptor. This
 * descriptor is documented in section 9.6.5 of the USB 3.0 specification.
 * All multiple-byte fields are represented in host-endian format.
 */
struct libusb_interface_descriptor {
  /** Size of this descriptor (in bytes) */
  uint8_t  bLength;

  /** Descriptor type. Will have value
   * \ref libusb_descriptor_type::LIBUSB_DT_INTERFACE LIBUSB_DT_INTERFACE
   * in this context. */
  uint8_t  bDescriptorType;

  /** Number of this interface */
  uint8_t  bInterfaceNumber;

  /** Value used to select this alternate setting for this interface */
  uint8_t  bAlternateSetting;

  /** Number of endpoints used by this interface (excluding the control
   * endpoint). */
  uint8_t  bNumEndpoints;

  /** USB-IF class code for this interface. See \ref libusb_class_code. */
  uint8_t  bInterfaceClass;

  /** USB-IF subclass code for this interface, qualified by the
   * bInterfaceClass value */
  uint8_t  bInterfaceSubClass;

  /** USB-IF protocol code for this interface, qualified by the
   * bInterfaceClass and bInterfaceSubClass values */
  uint8_t  bInterfaceProtocol;

  /** Index of string descriptor describing this interface */
  uint8_t  iInterface;

  /** Array of endpoint descriptors. This length of this array is determined
   * by the bNumEndpoints field. */
  const struct libusb_endpoint_descriptor *endpoint;

  /** Extra descriptors. If libusb encounters unknown interface descriptors,
   * it will store them here, should you wish to parse them. */
  const unsigned char *extra;

  /** Length of the extra descriptors, in bytes. */
  int extra_length;
};

/** \ingroup libusb_desc
 * A collection of alternate settings for a particular USB interface.
 */
struct libusb_interface {
  /** Array of interface descriptors. The length of this array is determined
   * by the num_altsetting field. */
  const struct libusb_interface_descriptor *altsetting;

  /** The number of alternate settings that belong to this interface */
  int num_altsetting;
};

/** \ingroup libusb_desc
 * Descriptor types as defined by the USB specification. */
enum libusb_descriptor_type {
  /** Device descriptor. See libusb_device_descriptor. */
      LIBUSB_DT_DEVICE = 0x01,

  /** Configuration descriptor. See libusb_config_descriptor. */
      LIBUSB_DT_CONFIG = 0x02,

  /** String descriptor */
      LIBUSB_DT_STRING = 0x03,

  /** Interface descriptor. See libusb_interface_descriptor. */
      LIBUSB_DT_INTERFACE = 0x04,

  /** Endpoint descriptor. See libusb_endpoint_descriptor. */
      LIBUSB_DT_ENDPOINT = 0x05,

  /** BOS descriptor */
      LIBUSB_DT_BOS = 0x0f,

  /** Device Capability descriptor */
      LIBUSB_DT_DEVICE_CAPABILITY = 0x10,

  /** HID descriptor */
      LIBUSB_DT_HID = 0x21,

  /** HID report descriptor */
      LIBUSB_DT_REPORT = 0x22,

  /** Physical descriptor */
      LIBUSB_DT_PHYSICAL = 0x23,

  /** Hub descriptor */
      LIBUSB_DT_HUB = 0x29,

  /** SuperSpeed Hub descriptor */
      LIBUSB_DT_SUPERSPEED_HUB = 0x2a,

  /** SuperSpeed Endpoint Companion descriptor */
      LIBUSB_DT_SS_ENDPOINT_COMPANION = 0x30
};

#define USB_MAXENDPOINTS	32
#define USB_MAXINTERFACES	32
#define USB_MAXCONFIG		8
#define LIBUSB_DT_INTERFACE_SIZE		9

#define DESC_HEADER_LENGTH		2
#define DEVICE_DESC_LENGTH		18
#define CONFIG_DESC_LENGTH		9
#define INTERFACE_DESC_LENGTH		9
#define ENDPOINT_DESC_LENGTH		7
#define ENDPOINT_AUDIO_DESC_LENGTH	9


/** @defgroup libusb_desc USB descriptors
 * This page details how to examine the various standard USB descriptors
 * for detected devices
 */

/* set host_endian if the w values are already in host endian format,
 * as opposed to bus endian. */
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
      case 'w':	/* 16-bit word, convert from little endian to CPU */
        dp += ((uintptr_t)dp & 1);	/* Align to word boundary */

        if (host_endian) {
          memcpy(dp, sp, 2);
        } else {
          w = (sp[1] << 8) | sp[0];
          *((uint16_t *)dp) = w;
        }
        sp += 2;
        dp += 2;
        break;
      case 'd':	/* 32-bit word, convert from little endian to CPU */
        dp += ((uintptr_t)dp & 1);	/* Align to word boundary */

        if (host_endian) {
          memcpy(dp, sp, 4);
        } else {
          d = (sp[3] << 24) | (sp[2] << 16) |
              (sp[1] << 8) | sp[0];
          *((uint32_t *)dp) = d;
        }
        sp += 4;
        dp += 4;
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

static inline void *usbi_reallocf(void *ptr, size_t size)
{
  void *ret = realloc(ptr, size);
  if (!ret)
    free(ptr);
  return ret;
}

static int parse_endpoint(struct libusb_endpoint_descriptor *endpoint, unsigned char *buffer,
                          int size, int host_endian)
{
  struct usb_descriptor_header header;
  unsigned char *extra;
  unsigned char *begin;
  int parsed = 0;
  int len;

  if (size < DESC_HEADER_LENGTH) {
    LOGE("short endpoint descriptor read %d/%d",
             size, DESC_HEADER_LENGTH);
    return LIBUSB_ERROR_IO;
  }

  usbi_parse_descriptor(buffer, "bb", &header, 0);
  if (header.bDescriptorType != LIBUSB_DT_ENDPOINT) {
    LOGE("unexpected descriptor %x (expected %x)",
             header.bDescriptorType, LIBUSB_DT_ENDPOINT);
    return parsed;
  }
  if (header.bLength > size) {
    LOGW("short endpoint descriptor read %d/%d",
              size, header.bLength);
    return parsed;
  }
  if (header.bLength >= ENDPOINT_AUDIO_DESC_LENGTH)
    usbi_parse_descriptor(buffer, "bbbbwbbb", endpoint, host_endian);
  else if (header.bLength >= ENDPOINT_DESC_LENGTH)
    usbi_parse_descriptor(buffer, "bbbbwb", endpoint, host_endian);
  else {
    LOGE("invalid endpoint bLength (%d)", header.bLength);
    return LIBUSB_ERROR_IO;
  }

  buffer += header.bLength;
  size -= header.bLength;
  parsed += header.bLength;

  /* Skip over the rest of the Class Specific or Vendor Specific */
  /*  descriptors */
  begin = buffer;
  while (size >= DESC_HEADER_LENGTH) {
    usbi_parse_descriptor(buffer, "bb", &header, 0);
    if (header.bLength < DESC_HEADER_LENGTH) {
      LOGE("invalid extra ep desc len (%d)",
               header.bLength);
      return LIBUSB_ERROR_IO;
    } else if (header.bLength > size) {
      LOGW("short extra ep desc read %d/%d",
                size, header.bLength);
      return parsed;
    }

    /* If we find another "proper" descriptor then we're done  */
    if ((header.bDescriptorType == LIBUSB_DT_ENDPOINT) ||
        (header.bDescriptorType == LIBUSB_DT_INTERFACE) ||
        (header.bDescriptorType == LIBUSB_DT_CONFIG) ||
        (header.bDescriptorType == LIBUSB_DT_DEVICE))
      break;

    LOGI("skipping descriptor %x", header.bDescriptorType);
    buffer += header.bLength;
    size -= header.bLength;
    parsed += header.bLength;
  }

  /* Copy any unknown descriptors into a storage area for drivers */
  /*  to later parse */
  len = (int)(buffer - begin);
  if (!len) {
    endpoint->extra = NULL;
    endpoint->extra_length = 0;
    return parsed;
  }

  extra = (unsigned char*)malloc(len);
  endpoint->extra = extra;
  if (!extra) {
    endpoint->extra_length = 0;
    return LIBUSB_ERROR_NO_MEM;
  }

  memcpy(extra, begin, len);
  endpoint->extra_length = len;

  return parsed;
}

static void clear_endpoint(struct libusb_endpoint_descriptor *endpoint)
{
  free((void *) endpoint->extra);
}

static void clear_interface(struct libusb_interface *usb_interface)
{
  int i;
  int j;

  if (usb_interface->altsetting) {
    for (i = 0; i < usb_interface->num_altsetting; i++) {
      struct libusb_interface_descriptor *ifp =
          (struct libusb_interface_descriptor *)
              usb_interface->altsetting + i;
      free((void *) ifp->extra);
      if (ifp->endpoint) {
        for (j = 0; j < ifp->bNumEndpoints; j++)
          clear_endpoint((struct libusb_endpoint_descriptor *)
                             ifp->endpoint + j);
      }
      free((void *) ifp->endpoint);
    }
  }
  free((void *) usb_interface->altsetting);
  usb_interface->altsetting = NULL;
}


static int parse_interface(struct libusb_interface *usb_interface, unsigned char *buffer, int size,
                           int host_endian)
{
  int i;
  int len;
  int r;
  int parsed = 0;
  int interface_number = -1;
  struct usb_descriptor_header header;
  struct libusb_interface_descriptor *ifp;
  unsigned char *begin;

  LOGI("********** beginning size: %d\n\n", size);
  for (int k = 0; k < size; k++) {
    LOGE("%d", (int)(buffer[k]));
  }
  LOGE("---------------------------------------------\n\n");
  usb_interface->num_altsetting = 0;

  while (size >= INTERFACE_DESC_LENGTH) {
    struct libusb_interface_descriptor *altsetting =
        (struct libusb_interface_descriptor *) usb_interface->altsetting;
    altsetting = (struct libusb_interface_descriptor *)usbi_reallocf(altsetting,
                                                                     sizeof(struct libusb_interface_descriptor) *
                                                                     (usb_interface->num_altsetting + 1));
    if (!altsetting) {
      r = LIBUSB_ERROR_NO_MEM;
      goto err;
    }
    usb_interface->altsetting = altsetting;

    ifp = altsetting + usb_interface->num_altsetting;
    usbi_parse_descriptor(buffer, "bbbbbbbbb", ifp, 0);
    if (ifp->bDescriptorType != LIBUSB_DT_INTERFACE) {
      LOGE("unexpected descriptor %x (expected %x)",
               ifp->bDescriptorType, LIBUSB_DT_INTERFACE);
      return parsed;
    }
    if (ifp->bLength < INTERFACE_DESC_LENGTH) {
      LOGE("invalid interface bLength (%d)",
               ifp->bLength);
      r = LIBUSB_ERROR_IO;
      goto err;
    }
    LOGE("********** round size: %d", size);
    LOGE("ifp->bLength: %d", ifp->bLength);
    LOGE("ifp->bNumEndPoints: %d", ifp->bNumEndpoints);
    if (ifp->bLength > size) {
      LOGW("short intf descriptor read %d/%d",
                size, ifp->bLength);
      return parsed;
    }
    if (ifp->bNumEndpoints > USB_MAXENDPOINTS) {
      LOGE("too many endpoints (%d)", ifp->bNumEndpoints);
      r = LIBUSB_ERROR_IO;
      goto err;
    }

    usb_interface->num_altsetting++;
    ifp->extra = NULL;
    ifp->extra_length = 0;
    ifp->endpoint = NULL;

    if (interface_number == -1)
      interface_number = ifp->bInterfaceNumber;

    /* Skip over the interface */
    buffer += ifp->bLength;
    parsed += ifp->bLength;
    size -= ifp->bLength;

    LOGE("after minus interface length: %d", size);

    begin = buffer;
    LOGE("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    for (int k = 0; k < size; k++) {
      LOGI("%d", (int)(buffer[k]));
    }
    LOGE("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    LOGE("______ header.bLength: %d, header.bDescriptorType: %d",
             header.bLength, header.bDescriptorType);
    header.bLength = 0x34;
    __asm("#DESC_BEGIN");
    /* Skip over any interface, class or vendor descriptors */
    while (size >= DESC_HEADER_LENGTH) {
      usbi_parse_descriptor(buffer, "bb", &header, 0);
      // __asm("#DESC_END");
      //      usbi_err(ctx, "header.bLength: %d, header.bDescriptorType: %d",
      //               header.bLength, header.bDescriptorType);
      if (header.bLength < DESC_HEADER_LENGTH) {
        LOGE("invalid extra intf desc len (%d)",
                 header.bLength);
        r = LIBUSB_ERROR_IO;
        goto err;
      } else if (header.bLength > size) {
        ///////////////////////////////////////////////////////////////////////////////////////////
        /// goes wrong here
        LOGW("short extra intf desc read %d/%d",
                  size, header.bLength);
        return parsed;
      }

      /* If we find another "proper" descriptor then we're done */
      if ((header.bDescriptorType == LIBUSB_DT_INTERFACE) ||
          (header.bDescriptorType == LIBUSB_DT_ENDPOINT) ||
          (header.bDescriptorType == LIBUSB_DT_CONFIG) ||
          (header.bDescriptorType == LIBUSB_DT_DEVICE))
        break;

      buffer += header.bLength;
      parsed += header.bLength;
      size -= header.bLength;
    }

    /* Copy any unknown descriptors into a storage area for */
    /*  drivers to later parse */
    len = (int)(buffer - begin);
    if (len) {
      ifp->extra = (unsigned char*)malloc(len);
      if (!ifp->extra) {
        r = LIBUSB_ERROR_NO_MEM;
        goto err;
      }
      memcpy((unsigned char *) ifp->extra, begin, len);
      ifp->extra_length = len;
    }

    if (ifp->bNumEndpoints > 0) {
      struct libusb_endpoint_descriptor *endpoint;
      endpoint = (struct libusb_endpoint_descriptor *)
          calloc(ifp->bNumEndpoints, sizeof(struct libusb_endpoint_descriptor));
      ifp->endpoint = endpoint;
      if (!endpoint) {
        r = LIBUSB_ERROR_NO_MEM;
        goto err;
      }

      for (i = 0; i < ifp->bNumEndpoints; i++) {
        r = parse_endpoint(endpoint + i, buffer, size,
                           host_endian);
        if (r < 0)
          goto err;
        if (r == 0) {
          ifp->bNumEndpoints = (uint8_t)i;
          break;;
        }
        LOGE("endpoint_size: %d", r);
        buffer += r;
        parsed += r;
        size -= r;
      }
    }

    /* We check to see if it's an alternate to this one */
    ifp = (struct libusb_interface_descriptor *) buffer;
    if (size < LIBUSB_DT_INTERFACE_SIZE ||
        ifp->bDescriptorType != LIBUSB_DT_INTERFACE ||
        ifp->bInterfaceNumber != interface_number)
      return parsed;
  }

  return parsed;
  err:
  clear_interface(usb_interface);
  return r;
}

int tmain() {
  struct libusb_interface *usb_interface;
  usb_interface = (struct libusb_interface *)
      calloc(1, sizeof(struct libusb_interface));
  unsigned char buffer[] = {9, 4, 0, 0, 0, 255, 0, 0, 0, 9,
                              4, 0, 1, 2, 255, 0, 0, 0, 7, 5,
                              1, 2, 0, 4, 0, 6, 48, 0, 0, 0,
                              0, 7, 5, 131, 1, 0, 4, 3, 6, 48,
                              15, 1, 0, 128, 9, 4, 0, 2, 2, 255,
                              0, 0, 0, 7, 5, 1, 2, 0, 4, 0,
                              6, 48, 0, 0, 0, 0, 7, 5, 131, 2,
                              0, 4, 0, 6, 48, 0, 0, 0, 0};
  parse_interface(usb_interface, buffer, sizeof(buffer), 0);
  return 0;
}