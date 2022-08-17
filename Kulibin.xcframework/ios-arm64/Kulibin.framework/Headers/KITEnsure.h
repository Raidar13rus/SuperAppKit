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

#define KIT_ENSURE_TYPE(OBJ, CLS, ...) (_KIT_ENSURE_CAST(CLS, ##__VA_ARGS__)_KIT_ENSURE_CHECK_JOIN(OBJ, [CLS self] KIT_VA_OPT_COMMA(__VA_ARGS__) KIT_MACRO_LIST(_KIT_ENSURE_PROTOCOLIFY, KIT_MACRO_LIST_COMMA_SEPARATOR,, ##__VA_ARGS__)))
#define _KIT_ENSURE_PROTOCOLIFY(I, CTX, PROTO) @protocol(PROTO)
#define _KIT_ENSURE_CHECK_JOIN(OBJ, CLS, ...) _KIT_ENSURE_CHECK(OBJ, CLS, ##__VA_ARGS__)

#define _KIT_ENSURE_CAST(...) _KIT_ENSURE_CAST_(KIT_MACRO_ARG_COUNT_ZOM(__VA_ARGS__), ##__VA_ARGS__)
#define _KIT_ENSURE_CAST_(N, ...) KIT_MACRO_CONCAT(_KIT_ENSURE_CAST_, N)(__VA_ARGS__)
#define _KIT_ENSURE_CAST_ZERO() (id)
#define _KIT_ENSURE_CAST_ONE(CLS) (CLS *)
#define _KIT_ENSURE_CAST_MANY(CLS, ...) (CLS<__VA_ARGS__> *)

#define _KIT_ENSURE_CHECK(OBJ, ...) _KIT_ENSURE_CHECK_(KIT_MACRO_ARG_COUNT_ZOM(__VA_ARGS__), OBJ, ##__VA_ARGS__)
#define _KIT_ENSURE_CHECK_(N, OBJ, ...) KIT_MACRO_CONCAT(_KIT_ENSURE_CHECK_, N)(OBJ, ##__VA_ARGS__)
#define _KIT_ENSURE_CHECK_CONFORMS(I, OBJ, PROTO) [OBJ conformsToProtocol: PROTO]
#define _KIT_ENSURE_CHECK_SEP(I, CTX) &&
#define _KIT_ENSURE_CHECK_ZERO(OBJ) (OBJ)
#define _KIT_ENSURE_CHECK_ONE(OBJ, CLS) ({ id __obj = (OBJ); [__obj isKindOfClass: CLS] ? __obj : nil; })
#define _KIT_ENSURE_CHECK_MANY(OBJ, CLS, ...) ({ id __obj = (OBJ); (([__obj isKindOfClass: CLS] && KIT_MACRO_LIST(_KIT_ENSURE_CHECK_CONFORMS, _KIT_ENSURE_CHECK_SEP, __obj, __VA_ARGS__)) ? __obj : nil); })

#define KIT_ENSURE_INLINE(OBJ, ...) ((id)_KIT_ENSURE_CHECK(OBJ, ##__VA_ARGS__))
#define KIT_ENSURE_CLASS(OBJ, CLASS) KIT_ENSURE_TYPE(OBJ, CLASS)
#define KIT_ENSURE_PROTO(OBJ, PROTO) KIT_ENSURE_TYPE(OBJ, NSObject, PROTO)
#define KIT_ENSURE_URL(...)     _KITEnsureURL(__VA_ARGS__)

#define KIT_ENSURE(...)         _KITEnsure(__VA_ARGS__, NULL)
#define KIT_ENSURE_DICT(...)    _KITEnsureDict(__VA_ARGS__)
#define KIT_ENSURE_ARRAY(...)   _KITEnsureArray(__VA_ARGS__)
#define KIT_ENSURE_STRING(...)  _KITEnsureString(__VA_ARGS__)
#define KIT_ENSURE_NUM(...)     _KITEnsureNum(__VA_ARGS__)
#define KIT_ENSURE_BOOL(...)    _KITEnsureBool(__VA_ARGS__)
#define KIT_ENSURE_DATE(...)    _KITEnsureDate(__VA_ARGS__)

KIT_EXPORT id            _KITEnsure(id, Class, ...) NS_REQUIRES_NIL_TERMINATION;
KIT_EXPORT NSDictionary *_KITEnsureDict(id);
KIT_EXPORT NSArray      *_KITEnsureArray(id);
KIT_EXPORT NSString     *_KITEnsureString(id);
KIT_EXPORT NSNumber     *_KITEnsureNum(id);
KIT_EXPORT BOOL          _KITEnsureBool(id);
KIT_EXPORT NSDate       *_KITEnsureDate(id);
KIT_EXPORT NSURL        *_KITEnsureURL(id);

KIT_EXPORT id KIT_ENSURED(id item, Class cls, void (^block)(id));

KIT_EXPORT id KIT_OBJECT_OR_NULL(id object);

KIT_EXPORT NSString *VKMXOR(NSString *text, const char *key);
