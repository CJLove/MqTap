//
// mq_tap.cpp - shared library that can be interposed between an
//			  	application and the actual librt.so.1
//
//            Usage:
//				$ export LD_PRELOAD=/path/to/libmqtap.so
//				$ <run application>
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mqueue.h>
#include <dlfcn.h>

// Typedefs to POSIX mq_*() functions used by the mq_tap library
typedef mqd_t(mq_open_func)(const char*, int, ...);
typedef int(mq_send_func)(mqd_t, const char*, size_t, unsigned int);
typedef int(mq_unlink_func)(const char*);
typedef int(mq_close_func)(mqd_t);


    // Forward declarations for C-callable functions
    void __attribute__ ((constructor)) mq_tap_init(void);
    void __attribute__ ((destructor)) mq_tap_fini(void);

    mqd_t mq_open(const char *__name, int __oflag, ...);
    int mq_send(mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len,
                unsigned int __msg_prio);
    int mq_close(mqd_t __mqdes);
    int mq_unlink(const char *__name);



// Entry point to initialize shared library
void mq_tap_init(void)
{
    //    printf("Initializing\n");    
    //    m_impl = new mq_tap_impl();
    //    if (false == m_impl->initialize()) {
    //        delete m_impl;
    //        m_impl = NULL;
    //    }
}

// Entry point to cleanup shared library
void mq_tap_fini(void)
{
    //    printf("Cleaning Up\n");
    //    if (NULL != m_impl) {
    //        m_impl->shutdown();
    //        delete m_impl;
    //        m_impl = NULL;
    //    }
}

// Replacement mq_open()
mqd_t mq_open(const char *__name, int __oflag, ...) 
{
    mq_open_func *librt_mq_open = NULL;

    void *handle = NULL;
    mqd_t mq_handle = (mqd_t)-1;
    char *error = NULL;

    // Get a handle to the actual mq_open() loaded from librt.so.1
    // (first time only)
    if (!librt_mq_open) {
#if defined(RHEL)
        handle = dlopen("/lib/tls/librt.so.1",RTLD_LAZY);
#else
        handle = dlopen("/lib/librt.so.1",RTLD_LAZY);
#endif
        if (!handle) {
            fputs(dlerror(), stderr);
            exit(1);
        }
        librt_mq_open = (mq_open_func*)dlsym(handle, "mq_open");
        if ((error = dlerror()) != NULL) {
            fprintf(stderr,"%s\n",error);
            exit(1);
        }
    }

    // Handle optional arguments and tap configuration if creating an mqueue
    mode_t mode = 0;
    struct mq_attr *attr = NULL;
    if (__oflag & O_CREAT) {
        va_list ap;

        va_start (ap, __oflag);
        mode = va_arg (ap, mode_t);
        attr = va_arg (ap, struct mq_attr *);
        va_end (ap);

        // Call the standard method
        mq_handle = librt_mq_open(__name,__oflag,mode,attr);
        //        printf("Calling mq_open(%s,%d) returns %d\n",__name,__oflag,mq_handle);                

        //        if ((NULL != m_impl) && (mq_handle != -1)) {
        //            m_impl->mq_open(librt_mq_open,mq_handle,__name,__oflag,mode,attr);
        //        }
    } else {
        // Call the standard method
        mq_handle = librt_mq_open(__name,__oflag,mode,attr);
        //        printf("Calling mq_open(%s,%d) returns %d\n",__name,__oflag,mq_handle);                        
    }
    return mq_handle;
}

// Replacement mq_close()
int mq_close(mqd_t __mqdes)
{
    static mq_close_func* librt_mq_close = NULL;

    void *handle = NULL;
    int result = 0;
    char *error = NULL;

    // Get a handle to the actual mq_close() loaded from librt.so.1
    // (first time only)
    if (!librt_mq_close) {
#if defined(RHEL)
        handle = dlopen("/lib/tls/librt.so.1",RTLD_LAZY);
#else
        handle = dlopen("/lib/librt.so.1",RTLD_LAZY);
#endif

        if (!handle) {
            fputs(dlerror(), stderr);
            exit(1);
        }
        librt_mq_close = (mq_close_func*)dlsym(handle, "mq_close");
        if ((error = dlerror()) != NULL) {
            fprintf(stderr,"%s\n",error);
            exit(1);
        }
    }
    //    printf("Calling mq_close()\n");
    //    if (NULL != m_impl) {
    //        m_impl->mq_close(librt_mq_close,__mqdes);
    //    }
    // Call the standard mq_close()
    result = librt_mq_close(__mqdes);
    return result;
}

// Replacement mq_unlink()
int mq_unlink(const char *__name)
{
    static mq_unlink_func* librt_mq_unlink = NULL;

    void *handle = NULL;
    int result = 0;
    char *error = NULL;

    // Get a handle to the actual mq_unlink() loaded from librt.so.1
    // (first time only)
    if (!librt_mq_unlink) {
#if defined(RHEL)
        handle = dlopen("/lib/tls/librt.so.1",RTLD_LAZY);
#else
        handle = dlopen("/lib/librt.so.1",RTLD_LAZY);
#endif

        if (!handle) {
            fputs(dlerror(), stderr);
            exit(1);
        }
        librt_mq_unlink = (mq_unlink_func*)dlsym(handle, "mq_unlink");
        if ((error = dlerror()) != NULL) {
            fprintf(stderr,"%s\n",error);
            exit(1);
        }
    }
    //    printf("Calling mq_unlink()\n");
    //    if (NULL != m_impl) {
    //        m_impl->mq_unlink(librt_mq_unlink,__name);
    //    }
    // Call the standard mq_unlink()
    result = librt_mq_unlink(__name);
    return result;
}    

// Replacement mq_send()
int mq_send(mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len,
            unsigned int __msg_prio)
{
    static mq_send_func* librt_mq_send = NULL;

    void *handle = NULL;
    int result = 0;
    char *error = NULL;

    // Get a handle to the actual mq_send() loaded from librt.so.1
    // (first time only)
    if (!librt_mq_send) {
#if defined(RHEL)
        handle = dlopen("/lib/tls/librt.so.1",RTLD_LAZY);
#else
        handle = dlopen("/lib/librt.so.1",RTLD_LAZY);
#endif

        if (!handle) {
            fputs(dlerror(), stderr);
            exit(1);
        }
        librt_mq_send = (mq_send_func*)dlsym(handle, "mq_send");
        if ((error = dlerror()) != NULL) {
            fprintf(stderr,"%s\n",error);
            exit(1);
        }
    }

    //    printf("Calling mq_send(%d)\n",__mqdes);
    //    if (NULL != m_impl) {
    //        m_impl->mq_send(librt_mq_send,__mqdes,__msg_ptr,__msg_len,__msg_prio);
    //    }
    // Call the standard mq_send()
    result = librt_mq_send(__mqdes,__msg_ptr,__msg_len,__msg_prio);
    return result;
}
