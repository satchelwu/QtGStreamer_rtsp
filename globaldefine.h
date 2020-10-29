#pragma once


struct GStreamer {
    static constexpr const char* SINK =        "sink";
    static constexpr const char* SRC =       "src";
    static constexpr const char* SINK_0 =     "sink_0";
    static constexpr const char* SINK_1 =     "sink_1";
    static constexpr const char*  SINK_2 =    "sink_2"  ;
    static constexpr const char*  SINK_3 =    "sink_3"  ;
    static constexpr const char*  SRC_0  =    "src_0"   ;
    static constexpr const char*  SRC_1  =    "src_1"   ;
    static constexpr const char*  SRC_2  =    "src_2"   ;
    static constexpr const char*  SRC_3  =    "src_3"   ;

    struct Plugin {
    static constexpr const char* qtquick2videosink  =  "qtquick2videosink" ;
    static constexpr const char* nvinfer            =  "nvinfer"           ;
    static constexpr const char* nvinferserver      =  "nvinferserver"     ;
    static constexpr const char* nvtracker          = "nvtracker"          ;
    static constexpr const char* nvstreammux        = "nvstreammux"        ;
    static constexpr const char* nvstreamdemux      = "nvstreamdemux"      ;
    static constexpr const char* nvdsosd            = "nvdsosd"            ;
    static constexpr const char* nvvideoconvert     = "nvvideoconvert"     ;
    static constexpr const char* nvjpegdec          = "nvjpegdec"          ;
    static constexpr const char* nvmsgconv          = "nvmsgconv"          ;
    static constexpr const char* nvmsgbroker        = "nvmsgbroker"        ;
    static constexpr const char* uridecodebin       = "uridecodebin"       ;
    static constexpr const char* videoconvert       = "videoconvert"       ;
    static constexpr const char* capsfilter         = "capsfilter"         ;
    static constexpr const char* filesink           = "filesink"           ;
    static constexpr const char* fakesink           = "fakesink"           ;
    static constexpr const char* tee                = "tee"                ;
    static constexpr const char* identity           = "identity"           ;
    static constexpr const char* nvvidconv          = "nvvidconv"          ;
    static constexpr const char* queue              = "queue";
    static constexpr const char* rtspsrc            = "rtspsrc";
    static constexpr const char* rtph264depay = "rtph264depay";
    static constexpr const char* rtph265depay = "rtph265depay";
    static constexpr const char* h264parse = "h264parse";
    static constexpr const char* h265parse = "h265parse";
    static constexpr const char* decodebin = "decodebin";
};

    struct rtspsrc{
        static constexpr const char* LOCATION = "location";
         static constexpr const char* LATENCY = "latency";
         static constexpr const char* DROP_ON_LATENCY = "drop-on-latency";
          static constexpr const char* PROTOCOLS = "protocols";
    };

    struct qtquick2videosink{
        static constexpr const char* ASYNC = "async";
        static constexpr const char* SYNC = "sync";
        static constexpr const char*  FORCE_ASPECT_RATIO = "force-aspect-ratio";
    };

};

struct Deepstream {



    struct nvinfer {
    static constexpr const char* CONFIG_FILE_PATH        =  "config-file-path";
    static constexpr const char* NUM_DETECTED_CLASSES    =  "num-detected-classes"   ;
    static constexpr const char* NET_SCALE_FACTOR        =  "net-scale-factor"       ;
    static constexpr const char* MODEL_FILE              = "model-file"              ;
    static constexpr const char* PROTO_FILE              = "proto-file"             ;
    static constexpr const char* INT8_CALIB_FILE         = "int8-calib-file"         ;
    static constexpr const char* BATCH_SIZE              = "batch-size"              ;
    static constexpr const char* MODEL_ENGINE_FILE       = "model-engine-file"       ;
    static constexpr const char* UFF_FILE                = "uff-file"                ;
    static constexpr const char* ONNX_FILE               = "onnx-file"               ;
    static constexpr const char* ENABLE_DBSCAN           = "enable-dbscan"           ;
    static constexpr const char* LABELFILE_PATH          = "labelfile-path"          ;
    static constexpr const char* MEAN_FILE               = "mean-file"               ;
    static constexpr const char* GIE_UNIQUE_ID           = "ie-unique-id"            ;
    static constexpr const char* OPERATE_ON_GIE_ID       = "operate-on-gie-id"       ;
    static constexpr const char* OPERATE_ON_CLASS_IDS    = "operate-on-class-ids"    ;
    static constexpr const char* INTERVAL                = "interval"                ;
    static constexpr const char* INPUT_OBJECT_MIN_WIDTH  = "input-object-min-width"  ;
    static constexpr const char* INPUT_OBJECT_MIN_HEIGHT = "input-object-min-height" ;
    static constexpr const char* INPUT_OBJECT_MAX_WIDTH  = "input-object-max-width"  ;
    static constexpr const char* INPUT_OBJECT_MAX_HEIGHT = "input-object-max-height" ;
    static constexpr const char* UFF_INPUT_DIMS          = "uff-input-dims"          ;
    static constexpr const char* NETWORK_MODE            = "network-mode"            ;
    static constexpr const char* OFFSETS                 = "offsets"                 ;
    static constexpr const char* OUTPUT_BLOB_NAMES       = "output-blob-names"       ;
    static constexpr const char* PARSE_BBOX_FUNC_NAME    = "parse-bbox-func-name"    ;
    static constexpr const char* CUSTOM_LIB_PATH         = "custom-lib-path"         ;
    static constexpr const char* MODEL_COLOR_FORMAT      = "model-color-format"      ;
    static constexpr const char* CLASSIFIER_ASYNC_MODE   = "classifier-async-mode"   ;
    static constexpr const char* PROCESS_MODE            = "process-mode"            ;
    static constexpr const char* CLASSIFIER_THRESHOLD    =     "classifier-threshold";
    static constexpr const char* UFF_INPUT_BLOB_NAME =   "uff-input-blob-name";
    static constexpr const char* SECONDARY_REINFER_INTERVAL ="secondary-reinfer-interval";
    static constexpr const char* OUTPUT_TENSOR_METE ="output-tensor-meta";
    static constexpr const char* ENABLE_DLA  ="enable-dla"                                     ;
    static constexpr const char* USE_DLA_CORE ="use-dla-core"                                  ;
    static constexpr const char* NETWORK_TYPE ="network-type"                                  ;
    static constexpr const char* MAINTAIN_ASPECT_RATIO ="maintain-aspect-ratio"                ;
    static constexpr const char* PARSE_CLASSIFIER_FUNC_NAME ="parse-classifier-func-name"      ;
    static constexpr const char* CUSTOM_NETWORK_CONFIG ="custom-network-config"                ;
    static constexpr const char* TLT_ENCODED_MODEL ="tlt-encoded-model"                        ;
    static constexpr const char* TLT_MODEL_KEY ="tlt-model-key"                                ;
    static constexpr const char* SEGMENTATION_THRESHOLD ="segmentation-threshold"              ;
    static constexpr const char* WORKSPACE_SIZE ="workspace-size"                              ;
    static constexpr const char* FORCE_IMPLICIT_BATCH_DIM ="force-implicit-batch-dim"          ;
    static constexpr const char* INFER_DIMS ="infer-dims"                                      ;
    static constexpr const char* ENGINE_CREATE_FUNC_NAME ="engine-create-func-name"            ;
    static constexpr const char* CLUSTER_MODE ="cluster-mode"                                  ;
    static constexpr const char* FILTER_OUT_CLASS_IDS ="filter-out-class-ids"                  ;
    static constexpr const char* SCALING_FILTER ="scaling-filter"                              ;
    static constexpr const char* SCALING_COMPUTE_HW ="scaling-compute-hw"                      ;



};
struct nvinferserver {

};
struct nvtracker {
    static constexpr const char* TRACKER_WIDTH= "tracker-width";
    static constexpr const char* TRACKER_HEIGHT ="tracker-height";
    static constexpr const char* LL_LIB_FILE ="ll-lib-file";
    static constexpr const char* LL_CONFIG_FILE= "ll-config-file";
    static constexpr const char* GPU_ID ="gpu-id";
    static constexpr const char* ENABLE_BATCH_PROCESS= "enable-batch-process";
    static constexpr const char* ENABEL_PAST_FRAME ="enable-past-frame";
};
struct  nvstreammux {
    static constexpr const char* BATCH_SIZE ="batch-size";
    static constexpr const char* BATCHED_PUSH_TIMEOUT= "batched-push-timeout";
    static constexpr const char* WIDTH ="width";
    static constexpr const char* HEIGHT ="height";
    static constexpr const char* ENABLE_PADDING= "enable-padding";
    static constexpr const char* GPU_ID ="gpu-id";
    static constexpr const char* LIVE_SOURCE ="live-source";
    static constexpr const char* NVBUF_MEMORY_TYPE= "nvbuf-memory-type";
    static constexpr const char* NUM_SURFACES_PER_FRAME= "num-surfaces-per-frame";
    static constexpr const char* BUFFER_POOL_SIZE ="buffer-pool-size";
    static constexpr const char* ATTACH_SYS_TS ="attach-sys-ts";
};
struct nvstreamdemux {

};

struct nvdsosd {
    static constexpr const char* NVBUF_MEMORY_TYPE= "nvbuf-memory-type";
    static constexpr const char* SRC_CROP= "src-crop";
    static constexpr const char* DST_CROP= "dst-crop";
    static constexpr const char* INTERPOLATION_METHOD= "interpolation-method";
    static constexpr const char* COMPUTE_HW ="compute-hw";
    static constexpr const char* GPU_ID= "gpu-id";
    static constexpr const char* OUTPUT_BUFFERS= "output-buffers";
};

struct nvvideoconvert {

};

struct nvmsgconv {

};

struct nvmsgbroker {

};


};


