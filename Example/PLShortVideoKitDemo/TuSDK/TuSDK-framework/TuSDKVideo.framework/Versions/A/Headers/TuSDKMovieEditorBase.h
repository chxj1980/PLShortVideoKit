//
//  TuSDKMovieEditorBase.h
//  TuSDKVideo
//
//  Created by Yanlin Qiu on 19/12/2016.
//  Copyright © 2016 TuSDK. All rights reserved.
//

#import "TuSDKVideoImport.h"
#import "TuSDKVideoResult.h"
#import "TuSDKMovieEditorOptions.h"
#import "TuSDKMediaEffectData.h"
#import "TuSDKTimeRange.h"
#import "TuSDKMVStickerAudioEffectData.h"
#import "TuSDKMediaSceneEffectData.h"
#import "TuSDKMovieEditorMode.h"

/**
 *  视频编辑基类
 */
@interface TuSDKMovieEditorBase : NSObject
{
    @protected
    
    // 视频视图
    TuSDKICFilterMovieViewWrap *_cameraView;
}

/**
 *  输入视频源 URL > Asset
 */
@property (nonatomic) NSURL *inputURL;

/**
 *  输入视频源 URL > Asset
 */
@property (nonatomic) AVAsset *inputAsset;

/**
 *  裁剪范围 （开始时间~持续时间）
 */
@property (nonatomic,strong) TuSDKTimeRange *cutTimeRange;

/**
 *  最小裁剪持续时间
 */
@property (nonatomic, assign) NSUInteger minCutDuration;

/**
 *  最大裁剪持续时间
 */
@property (nonatomic, assign) NSUInteger maxCutDuration;

/**
 *  保存到系统相册 (默认保存, 当设置为NO时, 保存到临时目录)
 */
@property (nonatomic) BOOL saveToAlbum;

/**
 *  保存到系统相册的相册名称
 */
@property (nonatomic, copy) NSString *saveToAlbumName;

/**
 *  视频覆盖区域颜色 (默认：[UIColor blackColor])
 */
@property (nonatomic, retain) UIColor *regionViewColor;

/**
 *  是否正在切换滤镜
 */
@property (nonatomic, readonly) BOOL isFilterChanging;

/**
 *  视频总持续时间
 */
@property(readonly,nonatomic) float duration;

/**
 *  视频实际总时长
 */
@property(readonly,nonatomic) float actualDuration;

/**
 *  TuSDKMovieEditor 状态
 */
@property (readonly,assign) lsqMovieEditorStatus status;

/**
 * 设置播放模式，默认正序播放
 */
@property (nonatomic,assign) lsqMovieEditorPlayMode playMode;

/**
 * 当前设置的时间特效 默认： lsqMovieEditorTimeEffectModeNone
 */
@property (nonatomic,readonly) lsqMovieEditorTimeEffectMode timeEffectMode;

/**
 *  导出视频的文件格式（默认:lsqFileTypeMPEG4）
 */
@property (nonatomic, assign) lsqFileType fileType;

/**
 *  预览时视频原音音量， 默认 1.0  注：仅在 option 中的 enableSound 为 YES 时有效
 */
@property (nonatomic, assign) CGFloat videoSoundVolume;
/**
 *  设置生效的特效模式  注：滤镜、场景特效、粒子特效不能同时添加，当 EfficientEffectMode 为Default时 以后添加的特效为准，当Mode进行限定时，则以限定的模式为准
 */
@property (nonatomic, assign) lsqMovieEditorEfficientEffectMode efficientEffectMode;

#pragma mark - waterMark

/**
 *  设置水印图片，最大边长不宜超过 500
 */
@property (nonatomic, retain) UIImage *waterMarkImage;

/**
 *  水印位置，默认 lsqWaterMarkBottomRight
 */
@property (nonatomic) lsqWaterMarkPosition waterMarkPosition;

#pragma mark - init

/**
 *  初始化
 *
 *  @param holderView 预览容器
 *  @return 对象实例
 */
- (instancetype)initWithPreview:(UIView *)holderView options:(TuSDKMovieEditorOptions *)options;

/**
 *  加载视频，显示第一帧
 */
- (void)loadVideo;

#pragma mark - Preview

/**
 *  启动预览
 */
- (void) startPreview;

/**
 *  停止预览
 */
- (void) stopPreview;

/**
 * 停止并重新开始预览
 * 如果你需要 stopPreView 紧接着使用 startPreView 再次启动预览，你首选的方案应为 rePreview，rePreview会根据内部状态在合适的时间启动预览
 */
- (void) rePreview;

/**
 * 暂停预览
 */
- (void) pausePreView;

/**
 *  是否正在预览视频
 *
 *  @return true/false
 */
- (BOOL) isPreviewing;

/**
 跳转至某一时间节点

 @param time 当前视频的时间节点(若以设置过裁剪时间段，该时间表示裁剪后时间表示)
 */
- (void) seekToPreviewWithTime:(CMTime)time;

#pragma mark - Record

/**
 *  开始录制视频 将被存储至文件
 */
- (void) startRecording;

/**
 *  取消录制
 */
- (void) cancelRecording;

/**
 *  是否正在录制视频
 *
 *  @return true/false
 */
- (Boolean) isRecording;

/**
 *  通知视频编辑器状态
 *
 *  @param status 状态信息
 */
- (void) notifyMovieEditorStatus:(lsqMovieEditorStatus) status;

/**
 *  通知视频处理进度事件
 *
 *  @param progress 进度 (0 ~1)
 */
- (void)notifyMovieProgress:(CGFloat)progress;

/**
 *  通知视频处理结果
 *
 *  @param result TuSDKVideoResult 对象
 *  @param error  错误信息
 *  
 *  @return
 */
- (void)notifyResult:(TuSDKVideoResult *)result error:(NSError *)error;

#pragma mark - switch filter

/**
 *  切换滤镜
 *
 *  @param code 滤镜代号
 *
 *  @return BOOL 是否成功切换滤镜
 */
- (BOOL)switchFilterWithCode:(NSString *)code;

#pragma mark - media effect

/**
 设置时间特效模式

 @param timeEffectMode 时间特效模式
 @param atTimeRange 特效生效时间
 @param times 特效次数
 */
- (void)setTimeEffectMode:(lsqMovieEditorTimeEffectMode)timeEffectMode atTimeRange:(TuSDKTimeRange *)timeRange times:(NSUInteger)times;

/**
 添加一个多媒体特效 (MV、配音中使用)

 @param effect 特效对象，需使用 MV 或 配音 对应的 TuSDKMediaEffectData 的子类
 */
- (void)addMediaEffect:(TuSDKMediaEffectData *)effect;

/**
 移除所有特效 (MV、配音中使用)
 */
- (void)removeAllMediaEffect;

#pragma mark - particle scene

/**
 开始添加特效  包含：场景特效、粒子特效  使用effectMode 进行区分

 @param particleCode 粒子特效code
 @param effectMode 特效类型
 @since      v2.0
 */
- (void)addEffectWithCode:(NSString *)particleCode withMode:(lsqMovieEditorEffectMode)effectMode;

/**
 结束正在添加的特效  包含：场景特效、粒子特效
 @param effectMode 特效类型
 @since      v2.0
 */
- (void)addEndEffectWithMode:(lsqMovieEditorEffectMode)effectMode;

/**
 取消正在添加的粒子特效
 @param effectMode 特效类型
 */
- (void)cancleAddingEffectWithMode:(lsqMovieEditorEffectMode)effectMode;

/**
 更新粒子特效的发射器位置
 
 @param point 粒子发射器位置  左上角为(0,0)  右下角为(1,1)
 @since      v2.0
 */
- (void)updateParticleEmitPosition:(CGPoint)point;

/**
 更新 下一次添加的 粒子特效材质大小  0~1  注：对当前正在添加或已添加的粒子不生效

 @param size 粒子特效材质大小
 @since      v2.0
 */
- (void)updateParticleEmitSize:(CGFloat)size;

/**
 更新 下一次添加的 粒子特效颜色  注：对当前正在添加或已添加的粒子不生效
 
 @param color 粒子特效颜色
 @since      v2.0
 */
- (void)updateParticleEmitColor:(UIColor *)color;

/**
 移除上一个添加的特效  包含：场景特效、粒子特效  使用effectMode 进行区分
 @param effectMode 特效类型
 @since      v2.0
 */
- (void)removeLastEffectWithMode:(lsqMovieEditorEffectMode)effectMode;

/**
 移除所有添加的特效  包含：场景特效、粒子特效  使用effectMode 进行区分
 @param effectMode 特效类型
 @since      v2.0
 */
- (void)removeAllEffectWithMode:(lsqMovieEditorEffectMode)effectMode;

#pragma mark - destroy

/**
 *  销毁
 */
- (void)destroy;

@end
