//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>
#include <runtime.h>
#include <show_images/show_images.h>

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    if (findArmorBox(src, target_box)) {  // 在原图中寻找目标，并返回是否找到
        if (last_box.rect != cv::Rect2d() &&
            (getPointLength(last_box.getCenter() - target_box.getCenter()) >
             last_box.rect.height * 2.0) &&
            anti_switch_cnt++ < 3) {
            // 判断当前目标和上次有效目标是否为同一个目标,并给３帧的时间，试图找到相同目标。即刚发生目标切换内的３帧内不发送目标位置。可以一定程度避免频繁多目标切换。
            target_box = ArmorBox();
            LOG(INFO) << "avoid_quick_switch!";
            return false;
        } else {
            anti_switch_cnt = 0;
            return true;
        }
    } else {  //串口没输出的话看这里
        target_box = ArmorBox();
        anti_switch_cnt++;
        return false;
    }
}

/*
bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    if (findArmorBox(src, target_box)) {
        return true;
    } else {
        target_box = ArmorBox();
        return false;
    }
}
*/