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

#ifndef Kulibin_Macros_h
#define Kulibin_Macros_h

#pragma mark - metapropgramming

#define KIT_MACRO_EMPTY()
#define KIT_MACRO_DEFER(ARG) ARG KIT_MACRO_EMPTY()
#define KIT_MACRO_OBSTRUCT(...) __VA_ARGS__ KIT_MACRO_DEFER(KIT_MACRO_EMPTY)()
#define KIT_MACRO_EXPAND(...) __VA_ARGS__

/// Converts series of macro tokens to string literal
#define KIT_MACRO_STRINGIZE(...) _KIT_MACRO_STRINGIZE_TIK_(__VA_ARGS__)
#define _KIT_MACRO_STRINGIZE_TOK(...) #__VA_ARGS__
#define _KIT_MACRO_STRINGIZE_TIK(...) _KIT_MACRO_STRINGIZE_TOK_(__VA_ARGS__)

/// Converts series of tokens to string literal
#define KIT_MACRO_TRIVIAL_STRINGIZE(...) #__VA_ARGS__

/// Concatenates two macro tokens
#define KIT_MACRO_CONCAT(...) _KIT_MACRO_CONCAT_TIK(__VA_ARGS__)
#define _KIT_MACRO_CONCAT_TOK(L, R) L ## R
#define _KIT_MACRO_CONCAT_TIK(...) _KIT_MACRO_CONCAT_TOK(__VA_ARGS__)

/// Concatenates two tokens
#define KIT_MACRO_TRIVIAL_CONCAT(L, R) L ## R

/// Expands to the number of variadic arguments passed, 0 ... 15
#define KIT_MACRO_ARG_COUNT(...) _KIT_MACRO_ARG_COUNT_(, ##__VA_ARGS__, _KIT_MACRO_ARG_SLOPE_DEC())
/// Expands to the number of variadic arguments passed in hex form, 0 ... F
#define KIT_MACRO_ARG_COUNT_HEX(...) _KIT_MACRO_ARG_COUNT_(, ##__VA_ARGS__, _KIT_MACRO_ARG_SLOPE_HEX())
/// Expands to either ONE, ZERO or MANY depending on number of variadic arguments passed
#define KIT_MACRO_ARG_COUNT_ZOM(...) _KIT_MACRO_ARG_COUNT_(, ##__VA_ARGS__, _KIT_MACRO_ARG_SLOPE_ZOM())
#define _KIT_MACRO_ARG_COUNT_(...) _KIT_MACRO_ARG_SLIDE(__VA_ARGS__)
#define _KIT_MACRO_ARG_SLIDE(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F, N, ...) N
#define _KIT_MACRO_ARG_SLOPE_DEC()   15,   14,   13,   12,   11,   10,    9,    8,    7,    6,    5,    4,    3,    2,   1,    0
#define _KIT_MACRO_ARG_SLOPE_HEX()    F,    E,    D,    C,    B,    A,    9,    8,    7,    6,    5,    4,    3,    2,   1,    0
#define _KIT_MACRO_ARG_SLOPE_ZOM() MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, ONE, ZERO

/// Expands to FUNC macro applied to each variadic parameter given, separated by SEP macro.
/// @param FUNC a macro to be applied. Pasted as FUNC(INDEX, CONTEXT, ELEMENT)
/// @param SEP a macro to be used as a separator between elements. Pasted as SEP(INDEX, CONTEXT)
/// @param CTX a value to be passed to FUNC and SEP macros, unchanged.
/// @param __VA_ARGS__ list of elements to be iterated over
/// @discussion usage:
///
///         #define PRINT(I, FMT, EL) NSLog(FMT, EL)
///         KIT_MACRO_LIST(PRINT, KITMACRO_LIST_SEMICOLON_SEPARATOR, @"Hello, %@!", @"world", @"user");
///
/// will be expanded to:
///
///         NSLog(@"Hello, %@!", @"world");NSLog(@"Hello, %@!", @"user");
///
#define KIT_MACRO_LIST(FUNC, SEP, CTX, ...) _KIT_MACRO_LIST_(KIT_MACRO_ARG_COUNT(__VA_ARGS__), FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_(I, FUNC, SEP, CTX, ...) KIT_MACRO_CONCAT(_KIT_MACRO_LIST_, I)(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_0(FUNC, SEP, CTX, X, ...)
#define _KIT_MACRO_LIST_1(FUNC, SEP, CTX, X, ...) FUNC(0,  CTX, X)
#define _KIT_MACRO_LIST_2(FUNC, SEP, CTX, X, ...) FUNC(1,  CTX, X)SEP(1,  CTX)_KIT_MACRO_LIST_1(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_3(FUNC, SEP, CTX, X, ...) FUNC(2,  CTX, X)SEP(2,  CTX)_KIT_MACRO_LIST_2(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_4(FUNC, SEP, CTX, X, ...) FUNC(3,  CTX, X)SEP(3,  CTX)_KIT_MACRO_LIST_3(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_5(FUNC, SEP, CTX, X, ...) FUNC(4,  CTX, X)SEP(4,  CTX)_KIT_MACRO_LIST_4(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_6(FUNC, SEP, CTX, X, ...) FUNC(5,  CTX, X)SEP(5,  CTX)_KIT_MACRO_LIST_5(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_7(FUNC, SEP, CTX, X, ...) FUNC(6,  CTX, X)SEP(6,  CTX)_KIT_MACRO_LIST_6(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_8(FUNC, SEP, CTX, X, ...) FUNC(7,  CTX, X)SEP(7,  CTX)_KIT_MACRO_LIST_7(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_9(FUNC, SEP, CTX, X, ...) FUNC(8,  CTX, X)SEP(8,  CTX)_KIT_MACRO_LIST_8(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_A(FUNC, SEP, CTX, X, ...) FUNC(9,  CTX, X)SEP(9,  CTX)_KIT_MACRO_LIST_9(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_B(FUNC, SEP, CTX, X, ...) FUNC(10, CTX, X)SEP(10, CTX)_KIT_MACRO_LIST_A(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_C(FUNC, SEP, CTX, X, ...) FUNC(11, CTX, X)SEP(11, CTX)_KIT_MACRO_LIST_B(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_D(FUNC, SEP, CTX, X, ...) FUNC(12, CTX, X)SEP(12, CTX)_KIT_MACRO_LIST_C(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_E(FUNC, SEP, CTX, X, ...) FUNC(13, CTX, X)SEP(13, CTX)_KIT_MACRO_LIST_D(FUNC, SEP, CTX, __VA_ARGS__)
#define _KIT_MACRO_LIST_F(FUNC, SEP, CTX, X, ...) FUNC(14, CTX, X)SEP(14, CTX)_KIT_MACRO_LIST_E(FUNC, SEP, CTX, __VA_ARGS__)

/// Predefined "," separator macro to be used with KIT_MACRO_LIST
#define KIT_MACRO_LIST_COMMA_SEPARATOR(I, CTX) ,
/// Predefined ";" separator macro to be used with KIT_MACRO_LIST
#define KIT_MACRO_LIST_SEMICOLON_SEPARATOR(I, CTX) ;
/// Predefined empty separator macro to be used with KIT_MACRO_LIST
#define KIT_MACRO_LIST_NO_SEPARATOR(I, CTX)

/// Produces comma token if variable argument list is non-empty, and nothing otherwise
#define KIT_VA_OPT_COMMA(...) _KIT_VA_OPT_COMMA_(KIT_MACRO_ARG_COUNT_ZOM(__VA_ARGS__), ##__VA_ARGS__)
#define _KIT_VA_OPT_COMMA_(N, ...) KIT_MACRO_CONCAT(_KIT_VA_OPT_COMMA_, N)
#define _KIT_VA_OPT_COMMA_ZERO
#define _KIT_VA_OPT_COMMA_ONE ,
#define _KIT_VA_OPT_COMMA_MANY ,


/// Preprocessor-compatible alternative to #pragma preprocessor directive;
/// @discussion usage:
///
///         KIT_MACRO_PRAGMA(mark - interface)
///
/// will be equivalent to:
///
///         #pragma mark - interface
///
#define KIT_MACRO_PRAGMA(...) _Pragma(KIT_MACRO_TRIVIAL_STRINGIZE(__VA_ARGS__))

/// Passes contextual information to the assembler
#define KIT_MACRO_ASM(...) __asm(#__VA_ARGS__)

#pragma mark - diagnostics and communication

/// Issues compile-time warning with given text
#define KIT_WARNING(...) KIT_MACRO_PRAGMA(GCC warning KIT_MACRO_TRIVIAL_STRINGIZE(__VA_ARGS__))

/// Issues compile-time error with given text
#define KIT_ERROR(...) KIT_MACRO_PRAGMA(GCC error KIT_MACRO_TRIVIAL_STRINGIZE(__VA_ARGS__))

#define _KIT_DIAGNOSTICS_ACTION(ACTION, ...) KIT_MACRO_LIST(_KIT_DIAGNOSTICS_ACTION_TIK, KIT_MACRO_LIST_NO_SEPARATOR, ACTION, __VA_ARGS__)
#define _KIT_DIAGNOSTICS_PITCH(ACTION) KIT_MACRO_PRAGMA(clang diagnostic ACTION)
#define _KIT_DIAGNOSTICS_ACTION_TIK(I, ACT, ARG) _KIT_DIAGNOSTICS_ACTION_TOK(I, ACT, _KIT_DIAGNOSTIC_NAME(ARG))
#define _KIT_DIAGNOSTICS_ACTION_TOK(I, ACT, ARG) _KIT_DIAGNOSTICS_PITCH(ACT KIT_MACRO_TRIVIAL_STRINGIZE(ARG))
#define _KIT_DIAGNOSTIC_NAME(ARG) -W ## ARG

/// Marks given diagnostics to be ignored till the end of the current translation unit.
/// Combine with KIT_DIAGNOSTICS_CONTEXT_BEGIN/END to limit the scope of this effect.
/// @discussion usage;
///
///         KIT_DIAGNOSTICS_IGNORE(unused-variable, unused-function)
///
#define KIT_DIAGNOSTICS_IGNORE(...) _KIT_DIAGNOSTICS_ACTION(ignored, __VA_ARGS__)

/// Marks given diagnostics as warnings till the end of the current translation unit.
/// Combine with KIT_DIAGNOSTICS_CONTEXT_BEGIN/END to limit the scope of this effect.
/// @see KIT_DIAGNOSTICS_IGNORE
#define KIT_DIAGNOSTICS_WARN(...)   _KIT_DIAGNOSTICS_ACTION(warning, __VA_ARGS__)

/// Marks given diagnostics as errors till the end of the current translation unit.
/// Combine with KIT_DIAGNOSTICS_CONTEXT_BEGIN/END to limit the scope of this effect.
/// @see KIT_DIAGNOSTICS_IGNORE
#define KIT_DIAGNOSTICS_ERROR(...)  _KIT_DIAGNOSTICS_ACTION(error, __VA_ARGS__)

/// Marks given diagnostics as fatal errors till the end of the current translation unit.
/// Combine with KIT_DIAGNOSTICS_CONTEXT_BEGIN/END to limit the scope of this effect.
/// @see KIT_DIAGNOSTICS_IGNORE
#define KIT_DIAGNOSTICS_FATAL(...)  _KIT_DIAGNOSTICS_ACTION(fatal, __VA_ARGS__)

/// Marks the beginning new diagnostics context.
/// All following diagnostics configuration changes will be discarded at the end of the scope.

#define KIT_DIAGNOSTICS_CONTEXT_BEGIN   _KIT_DIAGNOSTICS_PITCH(push)
/// Marks the end of current diagnostics context
/// @see KIT_DIAGNOSTICS_CONTEXT_BEGIN

#define KIT_DIAGNOSTICS_CONTEXT_END     _KIT_DIAGNOSTICS_PITCH(pop)

/// Defines whole diagnostics context as an expression
/// @discussion usage:
///
///         BOOL acceptsInteractionEvents = KIT_DIAGNOSTICS_SCOPE({
///             KIT_DIAGNOSTICS_IGNORE(deprecated)
///             BOOL result = UIApplication.sharedApplication.ignoringInteractionEvents;
///             !result;
///         });
///
#define KIT_DIAGNOSTICS_SCOPE(...) ({ KIT_DIAGNOSTICS_CONTEXT_BEGIN KIT_DIAGNOSTICS_IGNORE(unknown-warning-option, compound-token-split) (__VA_ARGS__); KIT_DIAGNOSTICS_CONTEXT_END })


#define KIT_DEPRECATED(...) KIT_OPTIONAL_ATTRIBUTE(deprecated, __VA_ARGS__)

#pragma mark - linkage control

/// Places attributed symbol into specific linker section(s)
/// @discussion usage:
///     KIT_LINKER_SECTION(__TEXT,cstring_literals,__my_custom_section_1,__my_custom_section_2)
///     const char *const kName = "RD"
#define KIT_LINKER_SECTION(...) KIT_REQUIRED_ATTRIBUTE(section, #__VA_ARGS__)

/// Returns an address to the beginning of the specified section
#define KIT_LINKER_SECTION_BEGIN(SEGMENT, SECTION) _KIT_LINKER_SECTION_TICK(SEGMENT, SECTION, start, __COUNTER__)

/// Returns an address to the end of the specified section
#define KIT_LINKER_SECTION_END(SEGMENT, SECTION) _KIT_LINKER_SECTION_TICK(SEGMENT, SECTION, end, __COUNTER__)

#define _KIT_LINKER_SECTION_TICK(SEGMENT, SECTION, ACT, TAG) _KIT_LINKER_SECTION_TOCK(SEGMENT, SECTION, ACT, TAG)
#define _KIT_LINKER_SECTION_TOCK(SEGMENT, SECTION, ACT, TAG) ({ \
    extern void *_kit_##ACT##SEGMENT##_##SECTION##TAG KIT_MACRO_ASM(section$##ACT##$##SEGMENT##$##SECTION); \
    (void *)&_kit_##ACT##SEGMENT##_##SECTION##TAG; \
})

#define KIT_WEAK KIT_REQUIRED_ATTRIBUTE(weak)

#pragma mark - attributes & builtins machinery

#ifdef __has_builtin
#define KIT_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
#define KIT_HAS_BUILTIN(...) 0
#endif

#ifdef __has_attribute
#define KIT_HAS_ATTRIBUTE(...) __has_attribute(__VA_ARGS__)
#else
#define KIT_HAS_ATTRIBUTE(...) 0
#endif

#ifdef __has_include
#define KIT_HAS_INCLUDE(...) __has_include(__VA_ARGS__)
#else
#define KIT_HAS_INCLUDE(...) 0
#endif

/// Marks declaration with given attribute if the compiler supports it.
/// Issues compile time warning otherwise.
#define KIT_OPTIONAL_ATTRIBUTE(ATTRIBUTE, ...) \
    KIT_MACRO_CONCAT(KIT_MACRO_DEFER(_KIT_OPTIONAL_ATTRIBUTE_), KIT_HAS_ATTRIBUTE(ATTRIBUTE))(ATTRIBUTE, __VA_ARGS__)
#define _KIT_OPTIONAL_ATTRIBUTE_0(ATTRIBUTE, ...) KIT_WARNING(attribute ATTRIBUTE is not supported)
#define _KIT_OPTIONAL_ATTRIBUTE_1(ATTRIBUTE, ...) __attribute__((ATTRIBUTE(__VA_ARGS__)))

/// Marks declaration with given attribute if the compiler supports it.
/// Issues compile time error otherwise.
#define KIT_REQUIRED_ATTRIBUTE(ATTRIBUTE, ...) \
    KIT_MACRO_CONCAT(_KIT_REQUIRED_ATTRIBUTE_, KIT_HAS_ATTRIBUTE(ATTRIBUTE))(ATTRIBUTE, __VA_ARGS__)
#define _KIT_REQUIRED_ATTRIBUTE_0(ATTRIBUTE, ...) KIT_ERROR(attribute ATTRIBUTE is not supported)
#define _KIT_REQUIRED_ATTRIBUTE_1(ATTRIBUTE, ...) __attribute__((ATTRIBUTE(__VA_ARGS__)))

#pragma mark - predefined attributes & builtins

/// Marks the position in code it resides on as unreachable, allowing compiler to issue more productive optimisations
/// and skip certain diagnostics (like missing-return-statement)
/// It is undefined behaviour if the control actually reaches code marked unreachable at runtime.
#if KIT_HAS_BUILTIN(unreachable)
#define KIT_UNREACHABLE __builtin_unreachable()
#else
#define KIT_UNREACHABLE do {} while(0)
#endif

#define KIT_ASSERT_UNREACHABLE NSCAssert(NO, @"This line must be unreachable during normal execution")

/// Suggests compiler that logical condition is (un)likely to be true, aiding branch prediction.
#if KIT_HAS_BUILTIN(__builtin_expect)
#define KIT_LIKELY(COND) (__builtin_expect((COND), 1))
#define KIT_UNLIKELY(COND) (__builtin_expect((COND), 0))
#else
#define KIT_LIKELY(COND) (COND)
#define KIT_UNLIKELY(COND) (COND)
#endif

/// Prevents marked class from being subclassed
#define KIT_FINAL_CLASS                     KIT_OPTIONAL_ATTRIBUTE(objc_subclassing_restricted)

/// Marks C object type as boxable, allowing it to be used with boxing expresion ( @(value) )
#define KIT_BOXABLE                         KIT_OPTIONAL_ATTRIBUTE(objc_boxable)

/// Marks part of the api unavailable
#define KIT_UNAVAILABLE(MESSAGE)            KIT_OPTIONAL_ATTRIBUTE(unavailable, MESSAGE)

/// Makes compiler issue a warning when result of marked function or method is left unused.
#define KIT_NODISCARD                       KIT_OPTIONAL_ATTRIBUTE(warn_unused_result)

/// Marks the omission of *break*, *return* or *continue* as intentional at the end of the case clause
#define KIT_FALLTHROUGH                     KIT_OPTIONAL_ATTRIBUTE(fallthrough)

/// Marks function to be run at the setup time of the application or dynamic shared object.
/// The running order is determined by priority, 0 being the highest
#define KIT_RUN_AT_STARTUP(PRIORITY)        KIT_REQUIRED_ATTRIBUTE(constructor, PRIORITY)

/// Marks function to be run at the teardown time of the application or dynamic shared object.
/// The running order is determined by priority, 0 being the highest
#define KIT_RUN_AT_SHUTDOWN(PRIORITY)       KIT_REQUIRED_ATTRIBUTE(destructor, PRIORITY)

/// Enables overloading for C functions
#define KIT_OVERLOADABLE                    KIT_REQUIRED_ATTRIBUTE(overloadable)

/// Opts out of message dispatch for selected Objective-C method
#define KIT_DIRECT                          KIT_OPTIONAL_ATTRIBUTE(objc_direct)

/// Sets enum extensibility. Accepted values are: open, closed
#define KIT_ENUM_EXTENSIBILITY(EXT) KIT_OPTIONAL_ATTRIBUTE(enum_extensibility, EXT)

/// Accepted values are: RETAINED, UNRETAINED, AUTORELEASED
#define KIT_RETURNS(RETENTION) KIT_MACRO_CONCAT(KIT_MACRO_DEFER(_KIT_RETURNS_), RETENTION)
#define _KIT_RETURNS_RETAINED __attribute__((ns_returns_retained))
#define _KIT_RETURNS_UNRETAINED __attribute__((ns_returns_unretained))
#define _KIT_RETURNS_AUTORELEASED __attribute__((ns_returns_autoreleased))

/// Marks method taking ownership of self
#define KIT_CONSUMES_SELF KIT_OPTIONAL_ATTRIBUTE(ns_consumes_self)

/// Marks argument function or method expecting to take ownership of
#define KIT_CONSUMED KIT_OPTIONAL_ATTRIBUTE(ns_consumed)

/// Controls whether a particular function (or Objective-C method) is imported into Swift as a throwing function, and if so, which dynamic convention it uses
/// Values are: none, null_result, zero_result, nonzero_result, nonnull_error
#define KIT_SWIFT_THROWS(convention) KIT_OPTIONAL_ATTRIBUTE(swift_error, convention)

#pragma mark - defer

/// Construct similar to swift's defer. Defered code blocks are run at the end of the current scope in reverse declaration order.
/// The way the scope being exited from doesn't matter, i.e. it can be early return, @throw or anything else.
/// @discussion usage:
///
///         [file open];
///         KIT_DEFER {
///             [file close];
///         };
///
#define KIT_DEFER \
KIT_REQUIRED_ATTRIBUTE(cleanup, _KITCallCleanupBlock) \
KIT_OPTIONAL_ATTRIBUTE(objc_precise_lifetime) \
KIT_OPTIONAL_ATTRIBUTE(unused) \
void (^const KIT_MACRO_CONCAT(_kit_anonymous_defer_guard_, __COUNTER__))(void) = ^

KIT_OPTIONAL_ATTRIBUTE(artificial)
KIT_OPTIONAL_ATTRIBUTE(unused)
static inline void _KITCallCleanupBlock(void (__autoreleasing ^const *block)(void)) { if (block != NULL && *block != nil)(*block)(); }

#pragma mark - language convenience

#if TARGET_OS_IOS
#define KIT_PRINCIPAL_PLATFORM_HEADER <UIKit/UIKit.h>
#define KIT_PRINCIPAL_PLATFORM_MODULE UIKit
#elif TARGET_OS_WATCH
#define KIT_PRINCIPAL_PLATFORM_HEADER <WatchKit/WatchKit.h>
#define KIT_PRINCIPAL_PLATFORM_MODULE WatchKit
#elif TARGET_OS_MAC
#define KIT_PRINCIPAL_PLATFORM_HEADER <AppKit/AppKit.h>
#define KIT_PRINCIPAL_PLATFORM_MODULE AppKit
#endif

#define KIT_ABSTRACT_METHOD
#define KIT_ABSTRACT_METHOD_IMPLEMENTATION { \
    @throw [NSException exceptionWithName:NSInternalInconsistencyException \
                                   reason:[NSString stringWithFormat:@"%s is an abstract method", __PRETTY_FUNCTION__] \
                                 userInfo:nil]; KIT_UNREACHABLE; \
}

#ifdef __cplusplus
#define KIT_EXPORT extern "C"
#else
#define KIT_EXPORT extern
#endif

#ifdef __cplusplus
#define KIT_NONOVERLAPPING __restrict
#else
#define KIT_NONOVERLAPPING restrict
#endif

#define KIT_WEAKIFY(VAR) __weak typeof(VAR) _weak_##VAR = (VAR)
#define KIT_STRONGIFY(VAR) __strong __typeof(VAR) VAR = _weak_##VAR

/// Marks selected method to be part of specified objective c method family
/// @param FAMILY: one of "none", "alloc", "copy", "init", "mutableCopy", or "new"
#define KIT_METHOD_FAMILY(FAMILY) KIT_OPTIONAL_ATTRIBUTE(objc_method_family, FAMILY)

#endif /* Kulibin_Macros_h */
