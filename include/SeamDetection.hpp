#pragma once
#include <opencv2/stitching/detail/camera.hpp>
#include <opencv2/cudaimgproc.hpp>

#include <vector>
#include <cmath>

#define MAX_MASK_WIDTH 2000
#define MAX_MASK_HEIGHT 1200
#define MIN_MASK_WIDTH 320
#define MIN_MASK_HEIGHT 240


class SeamDetector
{
private:
    std::vector<cv::cuda::GpuMat> gpu_seam_masks;
    std::vector<cv::cuda::GpuMat> texXmap; // texture remap x-coord
    std::vector<cv::cuda::GpuMat> texYmap; // texture remap y-coord
    std::vector<cv::Point> corners;
    std::vector<cv::Size> sizes;
    cv::Size mask_maxnorm_size, mask_minnorm_size;
    double warped_image_scale = 1.0;
    double work_scale = 1;
    size_t imgs_num = 0;
    bool isInit = false;
protected:
    bool warpedImage(const std::vector<cv::Mat>& imgs, const std::vector<cv::Mat>& Ks_f, const std::vector<cv::detail::CameraParams>& cameras);
public:
    bool getInit() const {return isInit;}
    std::vector<cv::Point> getCorners() const {return corners;}
    std::vector<cv::Size> getSizes() const {return sizes;}
    std::vector<cv::cuda::GpuMat> getXmap() const {return texXmap;}
    std::vector<cv::cuda::GpuMat> getYmap() const {return texYmap;}
    std::vector<cv::cuda::GpuMat> getSeams() const {return gpu_seam_masks;}
    void setMaxNormSizeMask(cv::Size& size){mask_maxnorm_size = size;}
    cv::Size getMaxNormSizeMask() const {return mask_maxnorm_size;}
    void setMinNormSizeMask(cv::Size& size){mask_minnorm_size = size;}
    cv::Size getMinNormSizeMask() const {return mask_minnorm_size;}
public:
    SeamDetector(const size_t num_imgs, const double warped_image_scale_) :
        imgs_num(num_imgs), warped_image_scale(warped_image_scale_),
        mask_maxnorm_size(MAX_MASK_WIDTH, MAX_MASK_HEIGHT), mask_minnorm_size(MIN_MASK_WIDTH, MIN_MASK_HEIGHT)
    {assert(num_imgs > 0);}
    bool init(const std::vector<cv::Mat>& imgs, const std::vector<cv::Mat>& Ks_f, const std::vector<cv::detail::CameraParams>& cameras);
};
