//
//  ConnectViewControllerPublic.h
//  ConnectSDK
//
//  Created by Otilio on 20/01/16.
//
//


#import "ConnectClient.h"


@interface ConnectViewController : UIViewController{
}

@property (nonatomic, weak, getter = getConnectClient) id<ConnectClientBase> connectClient;

@end
