/*
Copyright (c) 2020 - present, LLC “V Kontakte”

1. Permission is hereby granted to any person obtaining a copy of this Software to
use the Software without charge.

2. Restrictions
You may not modify, merge, publish, distribute, sublicense, and/or sell copies, 
create derivative works based upon the Software or any part thereof.

3. Termination
This License is effective until terminated. LLC “V Kontakte” may terminate this
License at any time without any without any negative consequences to our rights.
You may terminate this License at any time by deleting the Software and all copies
thereof. Upon termination of this license for any reason, you shall continue to be
bound by the provisions of Section 2 above.
Termination will be without prejudice to any rights LLC “V Kontakte” may have as
a result of this agreement.

4. Disclaimer of warranty and liability
THE SOFTWARE IS MADE AVAILABLE ON THE “AS IS” BASIS. LLC “V KONTAKTE” DISCLAIMS
ALL WARRANTIES THAT THE SOFTWARE MAY BE SUITABLE OR UNSUITABLE FOR ANY SPECIFIC
PURPOSES OF USE. LLC “V KONTAKTE” CAN NOT GUARANTEE AND DOES NOT PROMISE ANY
SPECIFIC RESULTS OF USE OF THE SOFTWARE.
UNDER NO SIRCUMSTANCES LLC “V KONTAKTE” BEAR LIABILITY TO THE LICENSEE OR ANY
THIRD PARTIES FOR ANY DAMAGE IN CONNECTION WITH USE OF THE SOFTWARE.
*/

#ifndef Kulibin_Common_h
#define Kulibin_Common_h

#import "KITLock.h"
#import "KITMacros.h"
#import "KITDevice.h"

NS_ASSUME_NONNULL_BEGIN

#define KIT_BACKGROUND_TASK_BEGIN()                                                                     \
    __block UIBackgroundTaskIdentifier _appBackgroundtaskID = ({                                        \
        UIBackgroundTaskIdentifier identifier;                                                          \
        if (KITAppStateMonitor.sharedInstance.isInBackground) {                                         \
            identifier = [[UIApplication kit_sharedApplication] beginBackgroundTaskWithExpirationHandler:^{\
                [[UIApplication kit_sharedApplication] endBackgroundTask:_appBackgroundtaskID];           \
            }];                                                                                         \
        } else {                                                                                        \
            identifier = UIBackgroundTaskInvalid;                                                       \
        }                                                                                               \
        identifier;                                                                                     \
    })

#define KIT_BACKGROUND_TASK_END()                                                                       \
    do {                                                                                                \
        if (_appBackgroundtaskID != UIBackgroundTaskInvalid) {                                          \
            [[UIApplication kit_sharedApplication] endBackgroundTask:_appBackgroundtaskID];               \
        }                                                                                               \
    } while (0)

KIT_EXPORT BOOL KITAreStringsEqual(NSString * _Nullable s1, NSString * _Nullable s2);
KIT_EXPORT BOOL KITAreObjectsEqual(id _Nullable obj1, id _Nullable obj2);

KIT_EXPORT void KITDispatchOnMainThread(dispatch_block_t _Nonnull block);
KIT_EXPORT void KITDispatchAfter(double delay, dispatch_queue_t _Nonnull queue, dispatch_block_t _Nonnull block);

KIT_EXPORT NSString * _Nonnull KITUniqueDeviceID(void);
KIT_EXPORT NSUUID * _Nonnull KITUniqueDeviceUUID(void);
KIT_EXPORT NSString * _Nonnull KITUniqueDeviceUUIDString(void);
KIT_EXPORT NSString * _Nonnull KITUniqueDeviceShortUUIDString(void);

KIT_EXPORT void * _Nullable KITAlignPointerUp(void * _Nullable pointer, size_t alignment);
KIT_EXPORT void * _Nullable KITAlignPointerDown(void * _Nullable pointer, size_t alignment);
KIT_EXPORT BOOL KITIsPointerAligned(void * _Nullable pointer, size_t alignment);
KIT_EXPORT BOOL KITIsBlock(id _Nonnull object);

KIT_EXPORT id _Nullable KITFilterJSONObject(id _Nullable data, id _Nullable (^NS_NOESCAPE map)(id));

NS_ASSUME_NONNULL_END

#endif // Kulibin_Common_h
