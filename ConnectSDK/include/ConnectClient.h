//
//  ConnectClient.h
//  CordovaLib
//
//  Created by Otilio on 27/08/15.
//
//




#define kConnectConfigKeyAutoConnect     @"autoConnect"
#define kConnectConfigKeyAutoStartCall   @"autoStartCall"
#define kConnectConfigKeyProcessId       @"processId"
#define kConnectConfigAppUrl             @"appUrl"

#define kOnConnectOnReceivedUrlNotification @"ConnectOnReceivedUrlNotification"

#pragma mark enums

typedef enum {
    UNDEFINED = -1,
    NOT_CONNECTED,
    IDLE,
    OUTBOUND_CALL_STARTING,
    OUTBOUND_CALL_TRYING,
    OUTBOUND_CALL_RINGING,
    INBOUND_CALL_RINGING,
    CALL_IN_PROGRESS,
    TRYING,
    DO_NOT_DISTURB
} ClientStatus;


#pragma mark ConnectVersionDescriptor
@interface ConnectVersion : NSObject{}
@property (nonatomic, weak) NSString *sdkVersion;
@property (nonatomic, weak) NSString *sdkServerVersion;
@property (nonatomic, weak) NSString *serverVersion;
@property (nonatomic, weak) NSString *serverMobileVersion;
@property BOOL compatibility;
@end


#pragma mark OperatorAvailability
@interface ConnectOperatorAvailability : NSObject{}
@property BOOL operatorAvailable;
@property long queueLength;
@property BOOL loggedOperator;
@end


#pragma mark ConnectMethodCallback
typedef void (^OnSuccessBlock)(NSDictionary *result);
typedef void (^OnFailBlock)(NSDictionary *result);

@interface ConnectMethodCallback<SuccessType, FailType> : NSObject{
    void (^_onSuccessBlock)(SuccessType result);
    void (^_onFailBlock)(FailType result);
}

-(id)initWithOnSuccess:(void (^)(SuccessType result))onSuccess onFail:(void (^)(FailType error))onFail;
-(id)initWithOnSuccessBlock:(OnSuccessBlock)onSuccess onFail:(OnFailBlock)onFail;
-(void)onSuccess:(SuccessType)result;
-(void)onFail:(FailType)result;
@end

#pragma mark ConnectClientProtocol

@protocol ConnectClientProtocol <NSObject>
-(void)onClientReady;

//for native step
-(UIView*)onGetStepView:(NSString*)stepId availableFrame:(CGRect)frame;
-(void)onStepViewWillClose:(UIView*)view stepId:(NSString*)stepId;

//for native step end
@optional
-(void)onRemoteTrying:(NSString*)callId;
-(void)onRemoteRinging:(NSString*)callId remotePeer:(NSString*) remotePeer;
-(void)onRemoteJoined:(NSString*)callId from:(NSString*)from partyInfo:(NSDictionary*)info;
-(void)onRemoteBye:(NSString*)callId remotePeer:(NSString*)remotePeer;
-(void)onRemoteBusy:(NSString*)callId remotePeer:(NSString*)remotePeer;
-(void)onLoginSuccess;
-(void)onLoginFailed:(NSString*)message;
-(void)onIncomingRinging:(NSString*)callId from:(NSString*)from partyInfo:(NSDictionary*)info;
-(void)onConnectionReady;
-(void)onConnectionError:(NSString*)message;
-(void)onConnectionClosed;
-(void)onCallFailed:(NSString*)message;
-(void)onCallEstablished:(NSString*)callId from:(NSString*)from partyInfo:(NSDictionary*)info;
-(void)onCallClosed:(NSString*)callId;
-(void)onCallForwarded:(NSString*)callId;

@end

#pragma mark ConnectClientBase

@protocol ConnectClientBase
@property (nonatomic, strong) id<ConnectClientProtocol> delegate;
@property (nonatomic, strong) NSDictionary *config;


-(void)startCall:(ConnectMethodCallback*)callback;
-(void)startCallWithPlace:(NSString*)destinationPlace acceptVideo:(BOOL)acceptVideo acceptAudio:(BOOL)acceptAudio callback:(ConnectMethodCallback*)callback;

-(void)stopCall:(ConnectMethodCallback*)callback;
-(void)connect:(ConnectMethodCallback*)callback;
-(void)disconnect:(ConnectMethodCallback*)callback;
-(void)getStatus:(ConnectMethodCallback*)callback;

//for native step
-(void)notifyStepStatus:(NSString*)statusMessage callback:(ConnectMethodCallback*)callback;
-(void)setStepResult:(NSString*)result callback:(ConnectMethodCallback*)callback;
//for native step end

-(void)initWithDelegate:(id<ConnectClientProtocol>)delegate config:(NSDictionary*)config;

+(void)getSessionTokenWithData:(NSDictionary*)startupData fromServer:(NSString*)server callback:(ConnectMethodCallback*)callback;
+(void)checkVersion:(NSString*)server callback:(ConnectMethodCallback<ConnectVersion*, NSString*>*)callback;
+(void)getOperatorAvailability:(NSString*)server callback:(ConnectMethodCallback<ConnectOperatorAvailability*, NSString*>*)callback;
+(void)getServerAddress:(NSString*)entryPointUrl callback:(ConnectMethodCallback<NSString*, NSString*>*)callback;
+(NSString*)getVersion;
@end

#pragma mark ConnectClient

@interface ConnectClient<ConnectClientBase>

@end


