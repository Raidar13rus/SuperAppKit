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
#import "KITStreamTransform.h"
#import "KITMacros.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSStream (Kulibin)

/// Reads data from one stream and writes it to another.
/// Stream states are not automatically managed.
/// @param inputStream Stream to read data from. Have to be open prior call
/// @param outputStream Stream to write data to. Have to be open prior call
/// @param windowSize Amount of data to be read and written at each step. Pass 0 for default value
/// @param progressBlock Block to be called after each step with number of total bytes writted during entire operation.
///     If NO is returned, the operation immediately aborts and error if set is passed to callee.
+ (BOOL)transfuseFromStream:(NSInputStream *)inputStream
                   toStream:(NSOutputStream *)outputStream
             withWindowSize:(NSUInteger)windowSize
       callingProgressBlock:(BOOL (NS_NOESCAPE ^_Nullable)(NSUInteger totalBytes, NSError *_Nullable *error))progressBlock
                      error:(out NSError *__autoreleasing _Nullable *_Nullable)error;

@end

typedef NSInteger (^KITStreamReaderBlock)(uint8_t *data, NSUInteger size, NSError *_Nullable *error);

extern NSStreamPropertyKey const kNSStreamEstimatedTotalBytesCount;

@interface NSInputStream (Kulibin)

/// Estimated stream content total bytes count
/// Essentially the same as calling propertyForKey: with `kNSStreamEstimatedTotalBytesCount`
@property (nonatomic) NSUInteger estimatedTotalBytesCount;

/// Creates a stream representing consecutive data in all passed streams
/// @param stream Nil-terminated list of stream objects to be joined. Streams are automatically managed.
+ (instancetype)inputStreamJoiningStreams:(NSInputStream *_Nullable)stream, ... NS_REQUIRES_NIL_TERMINATION;

/// Array-based alternative to inputStreamJoiningStreams:
/// @param streams Array of zero or more stream objects to be joined. Streams are automatically managed
+ (instancetype)inputStreamJoiningStreamsInArray:(NSArray<NSInputStream *> *)streams;

/// Creates a stream using block to produce its data. Getting buffer is not supported.
/// @param block A block object used at each call to read:maxLength:.
///     Returning an error makes stream transition to NSStreamStatusAtError.
///     Returning zero makes stream transition to NSStreamStatusAtEnd.
+ (instancetype)inputStreamWithBlock:(KITStreamReaderBlock)block;

/// Creates a stream that passes read data through transform object
/// @param stream Wrapped stream object. Automatically managed.
/// @param transform Transform to be applied. Copied in
+ (instancetype)inputStreamWithStream:(NSInputStream *)stream applyingTransform:(id<KITStreamTransforming>)transform;

/// Creates a stream representing consecutive data in all passed streams
/// @param stream Nil-terminated list of stream objects to be joined. Streams are automatically managed.
- (instancetype)initJoiningStreams:(NSInputStream *_Nullable)stream, ... NS_REQUIRES_NIL_TERMINATION;

/// Alternative to initJoiningStreams: taking va_list
/// @param streams nil_terminated va_list of stream objects to be joined. Streams are automatically managed.
- (instancetype)initJoiningStreamsV:(va_list)streams;

/// Array-based alternative to initJoiningStreams:
/// @param streams Array of zero or more stream objects to be joined. Streams are automatically managed
- (instancetype)initJoiningStreamsInArray:(NSArray<NSInputStream *> *)streams;


/// Creates a stream using block to produce its data. Getting buffer is not supported.
/// @param block A block used at each call to read:maxLength:.
///     Returning an error makes stream transition to NSStreamStatusAtError.
///     Returning zero makes stream transition to NSStreamStatusAtEnd.
- (instancetype)initWithBlock:(KITStreamReaderBlock)block;

/// Creates a stream that passes read data through transform object
/// @param stream Wrapped stream object. Automatically managed.
/// @param transform Transform to be applied. Copied in
- (instancetype)initWithStream:(NSInputStream *)stream applyingTransform:(id<KITStreamTransforming>)transform;

/// Reads up to size data from stream or until it temporarily or permanently exhausted
/// @param size Amount of data to be read in bytes. Resulting NSData.length is no greater than this value.
/// @param error If error occured, contains self.streamError
/// @return NSData object containing data, or nil if error occured
- (NSData *_Nullable)readDataWithMaxSize:(NSUInteger)size error:(out NSError *_Nullable __autoreleasing *_Nullable)error;

/// Reads data from stream until it temporarily or permanently exhausted
/// @param error If error occured, contains self.streamError
/// @return NSData object containing data, or nil if error occured
- (NSData *_Nullable)readDataWithError:(out NSError *_Nullable __autoreleasing *_Nullable)error;

/// Creates a stream that passes data read from current stream through transform object
/// @param transform tranform object to be applied. Copied in.
- (instancetype)streamByApplyingTransform:(id<KITStreamTransforming>)transform KIT_NODISCARD;


/// Reads data from current stream and writes it to another.
/// Stream states are not automatically managed.
/// @param outputStream Stream to write data to. Have to be open prior call
/// @param windowSize Amount of data to be read and written at each step. Pass 0 for default value
/// @param progressBlock Block to be called after each step with number of total bytes writted during entire operation.
///     If NO is returned, the operation immediately aborts and error if set is passed to callee.
- (BOOL)transfuseRemainingToStream:(NSOutputStream *)outputStream
                    withWindowSize:(NSUInteger)windowSize
              callingProgressBlock:(BOOL (NS_NOESCAPE ^_Nullable)(NSUInteger totalBytes, NSError *_Nullable *error))progressBlock
                             error:(out NSError *__autoreleasing _Nullable *_Nullable)error;

@end

typedef NSInteger (^KITStreamWriterBlock)(const uint8_t *data, NSUInteger size, NSError *_Nullable *error);

@interface NSOutputStream (Kulibin)

@property (nonatomic, readonly, nullable) NSData *dataWrittenToMemory;

/// Creates stream that uses block to store its data
/// @param block A block object used at each call to write:length:.
///     Returning an error makes stream transition to NSStreamStatusAtError.
///     Returning zero makes stream transition to NSStreamStatusAtEnd.
+ (instancetype)outputStreamWithBlock:(KITStreamWriterBlock)block;

/// Creates a stream that passes written data through transform object
/// @param stream Wrapped stream object. Automatically managed.
/// @param transform Transform to be applied. Copied in
+ (instancetype)outputStreamWithStream:(NSOutputStream *)stream applyingTransform:(id<KITStreamTransforming>)transform;

/// Creates stream that uses block to store its data
/// @param block A block object used at each call to write:length:.
///     Returning an error makes stream transition to NSStreamStatusAtError.
///     Returning zero makes stream transition to NSStreamStatusAtEnd.
- (instancetype)initWithBlock:(KITStreamWriterBlock)block;

/// Creates a stream that passes written data through transform object
/// @param stream Wrapped stream object. Automatically managed.
/// @param transform Transform to be applied. Copied in
- (instancetype)initWithStream:(NSOutputStream *)stream applyingTransform:(id<KITStreamTransforming>)transform;

/// Writes the contents of NSData object to self.
/// @param data NSData object to write
/// @param error if NO is returned contains self.streamError
/// @return NO if error occured during write or stream gets exhausted before all data is written. Otherwise YES
- (BOOL)writeData:(NSData *)data error:(out NSError *_Nullable __autoreleasing *_Nullable)error;

/// Writes the contents of given buffer completely
/// @param buffer Buffer containing at least length bytes
/// @param length number of bytes to be writtein
/// @return -1 if error occured or stream exhausted before all data was written. length otherwise.
- (NSInteger)write:(const uint8_t *)buffer length:(NSUInteger)length;

/// Creates a stream that passes data written to current stream through transform object
/// @param transform tranform object to be applied. Copied in.
- (instancetype)streamByApplyingTransform:(id<KITStreamTransforming>)transform KIT_NODISCARD;

@end

NS_ASSUME_NONNULL_END
