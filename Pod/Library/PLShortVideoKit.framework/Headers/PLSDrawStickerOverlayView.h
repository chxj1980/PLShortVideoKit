//
//  PLSDrawStickerOverlayView.h
//  PLShortVideoKit
//
//  Created by hxiongan on 2018/4/11.
//  Copyright © 2018年 Pili Engineering, Qiniu Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PLSEditingProtocol.h"
#import "PLSTypeDefines.h"

/*!
 @interface PLSDrawStickerOverlayView
 @abstract
 文字、贴图、涂鸦的附着 View，用于替换 PLSVideoEditingView
 为了便于在 PLShortVideoEditor 的 preview 上直接做文字、贴图、涂鸦工作，不再需要跳转到另外的页面
 
 @since @1.11.0
 */
@interface PLSDrawStickerOverlayView : UIScrollView
<
PLSEditingProtocol
>

/** 视频显示范围*/
@property (nonatomic, assign) CGRect displayRect;
/** 剪切范围 */
@property (nonatomic, assign) CGRect cropRect;
/** 水印层 */
@property (nonatomic, weak, readonly) UIView *overlayView;

@end
