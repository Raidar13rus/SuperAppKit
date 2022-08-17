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

#import <Foundation/Foundation.h>
#import "KITMacros.h"

/// Once expression
/// Executes argument expression exactly once and remembers its value
/// @discussion usage:
///
///         result = KIT_ONCE_EXPR([MySingletonClass new]);
///
#define KIT_ONCE_EXPR(...) ({ \
    static __typeof(__VA_ARGS__) _val; \
    static dispatch_once_t _token; \
    dispatch_once(&_token, ^{ _val = (__VA_ARGS__); }); \
    _val; \
})


/// Synchronized expression
/// Provides a critical section using provided lock for given expression
/// @discussion usage:
///
///         KIT_SYNC_EXPR(self.lock, {
///             MySynchronizedCall();
///         });
///
///         result = KIT_SYNC_EXPR(self.lock, MySynchronizedCall());
///
#define KIT_SYNC_EXPR(LOCK, ...) \
    ({ KIT_LOCK_SCOPE(LOCK); (__VA_ARGS__); })

/// Scope lock-guard. Locks given lock and unlocks it at the exit of the current scope
/// @discussion usage:
///
///         KIT_LOCK_SCOPE(self.lock1, self.lock2);
///
#define KIT_LOCK_SCOPE(...) \
    KIT_DIAGNOSTICS_CONTEXT_BEGIN \
    KIT_DIAGNOSTICS_IGNORE(used-but-marked-unused) \
    KIT_REQUIRED_ATTRIBUTE(cleanup, _KITLockGuardCleanup) \
    KIT_OPTIONAL_ATTRIBUTE(objc_precise_lifetime) \
    KIT_OPTIONAL_ATTRIBUTE(unused) \
    const id<NSLocking> KIT_MACRO_CONCAT(_kit_anonymous_lock_guard_, __COUNTER__) = ({ \
        __strong id<NSLocking> lock = [KITMultilock lockWithLocks:__VA_ARGS__, nil]; \
        [lock lock]; \
        lock; \
    }) \
    KIT_DIAGNOSTICS_CONTEXT_END


#define KIT_DEFER_UNLOCK(LOCK) \
    KIT_DIAGNOSTICS_CONTEXT_BEGIN \
    KIT_DIAGNOSTICS_IGNORE(used-but-marked-unused) \
    KIT_REQUIRED_ATTRIBUTE(cleanup, _KITLockGuardCleanup) \
    KIT_OPTIONAL_ATTRIBUTE(objc_precise_lifetime) \
    KIT_OPTIONAL_ATTRIBUTE(unused) \
    __strong id<NSLocking> KIT_MACRO_CONCAT(_kit_anonymous_lock_guard_, __COUNTER__) = (LOCK) \
    KIT_DIAGNOSTICS_CONTEXT_END


typedef NS_ENUM(NSUInteger, LockType) {
    LockTypeNonRecursive = 0,
    LockTypeRecursive,
};

extern NSExceptionName KITLockingException;

#pragma mark - KITLock

@interface KITLock : NSObject <NSLocking>

@property (nonatomic, assign) LockType lockType;

- (instancetype)initWithLockType:(LockType)lockType NS_DESIGNATED_INITIALIZER;
- (void)lockWithBlock:(dispatch_block_t)block;

@end

#pragma mark - KITMutexLock

@interface KITMutexLock : NSObject <NSLocking>

@property (nonatomic, assign) LockType lockType;

- (instancetype)initWithLockType:(LockType)lockType NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - KITReadWriteLock

@interface KITSharedLock : NSObject <NSLocking>

- (void)lockExclusively:(BOOL)isExclusive NS_SWIFT_NAME(lock(exclusively:));

@end

#pragma mark - KITUnfairLock

@interface KITUnfairLock : NSObject <NSLocking>
@end

#pragma mark - KITMultilock

KIT_FINAL_CLASS
@interface KITMultilock : NSObject <NSLocking>

+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)lockWithLocks:(id<NSLocking>)locks, ... NS_REQUIRES_NIL_TERMINATION;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithLocks:(id<NSLocking>)locks, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithLocks:(__strong const id<NSLocking> *)locks count:(size_t)count NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - Internals

KIT_OPTIONAL_ATTRIBUTE(artificial)
KIT_OPTIONAL_ATTRIBUTE(unused)
static inline void _KITLockGuardCleanup(__autoreleasing const id<NSLocking> *lock) { if (lock != NULL) [*lock unlock]; }
