//
//  SGProgressWindow.m
//  Today
//
//  Created by Dmitry Khrykin on 8/17/19.
//  Copyright © 2019 Dmitry Khrykin. All rights reserved.
//

#import "SGProgressWindow.h"

@interface SGProgressWindow ()

@end

@implementation SGProgressWindow
@synthesize progressIndicatior = _progressIndicatior;

- (instancetype)init {
    if (self = [super init]) {
        self.titlebarAppearsTransparent = YES;
        self.styleMask |= NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskFullSizeContentView;

        NSVisualEffectView *visualEffectView = [[NSVisualEffectView alloc] init];
        visualEffectView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

        NSStackView *contentView = [[NSStackView alloc] init];
        contentView.edgeInsets = NSEdgeInsetsMake(20 + 22, 20, 20, 20);
        contentView.orientation = NSUserInterfaceLayoutOrientationVertical;
        contentView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;


        [visualEffectView addSubview:contentView];
        [contentView release];

        NSProgressIndicator *progressIndicatior = [[NSProgressIndicator alloc] init];
        progressIndicatior.indeterminate = YES;
        [progressIndicatior startAnimation:nil];

        _progressIndicatior = progressIndicatior;
        [contentView addArrangedSubview:progressIndicatior];
        [progressIndicatior release];

        self.contentView = visualEffectView;
        [visualEffectView release];

        [self setContentSize:NSMakeSize(350, 50)];
        [self center];
    }

    return self;
}
@end
