module;
#include <Common/interface/RefCntAutoPtr.hpp>
#include <Common/interface/ThreadPool.h>
#include <Graphics/GraphicsEngine/interface/APIInfo.h>
#include <Graphics/GraphicsEngine/interface/BlendState.h>
#include <Graphics/GraphicsEngine/interface/BottomLevelAS.h>
#include <Graphics/GraphicsEngine/interface/Buffer.h>
#include <Graphics/GraphicsEngine/interface/BufferView.h>
#include <Graphics/GraphicsEngine/interface/CommandList.h>
#include <Graphics/GraphicsEngine/interface/CommandQueue.h>
#include <Graphics/GraphicsEngine/interface/Dearchiver.h>
#include <Graphics/GraphicsEngine/interface/DepthStencilState.h>
#include <Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <Graphics/GraphicsEngine/interface/DeviceMemory.h>
#include <Graphics/GraphicsEngine/interface/DeviceObject.h>
#include <Graphics/GraphicsEngine/interface/EngineFactory.h>
#include <Graphics/GraphicsEngine/interface/Fence.h>
#include <Graphics/GraphicsEngine/interface/Framebuffer.h>
#include <Graphics/GraphicsEngine/interface/GraphicsTypes.h>
#include <Graphics/GraphicsEngine/interface/GraphicsTypesX.hpp>
#include <Graphics/GraphicsEngine/interface/InputLayout.h>
#include <Graphics/GraphicsEngine/interface/PipelineResourceSignature.h>
#include <Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Graphics/GraphicsEngine/interface/PipelineStateCache.h>
#include <Graphics/GraphicsEngine/interface/Query.h>
#include <Graphics/GraphicsEngine/interface/RasterizerState.h>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/RenderPass.h>
#include <Graphics/GraphicsEngine/interface/ResourceMapping.h>
#include <Graphics/GraphicsEngine/interface/Sampler.h>
#include <Graphics/GraphicsEngine/interface/Shader.h>
#include <Graphics/GraphicsEngine/interface/ShaderBindingTable.h>
#include <Graphics/GraphicsEngine/interface/ShaderResourceBinding.h>
#include <Graphics/GraphicsEngine/interface/ShaderResourceVariable.h>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>
#include <Graphics/GraphicsEngine/interface/Texture.h>
#include <Graphics/GraphicsEngine/interface/TextureView.h>
#include <Graphics/GraphicsEngine/interface/TopLevelAS.h>
#include <Platforms/interface/NativeWindow.h>
#include <Primitives/interface/BasicTypes.h>
#include <Primitives/interface/DataBlob.h>
#include <Primitives/interface/DebugOutput.h>
#include <Primitives/interface/FileStream.h>
#include <Primitives/interface/InterfaceID.h>
#include <Primitives/interface/MemoryAllocator.h>
#include <Primitives/interface/Object.h>
#include <Primitives/interface/ReferenceCounters.h>

// Factories require linking the corresponding Diligent backend when called.
// Vulkan factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS
    #include <Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#endif

// Native interfaces are available when their SDK headers are on the include path.
// Vulkan native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS) && __has_include(<vulkan/vulkan.h>)
// SDK types must precede Diligent interfaces; preserve this include order.

    #include <vulkan/vulkan.h>

    #include <Graphics/GraphicsEngineVulkan/interface/BottomLevelASVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/BufferViewVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/BufferVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/CommandQueueVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/DeviceContextVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/DeviceMemoryVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/FenceVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/FramebufferVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/PipelineStateCacheVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/PipelineStateVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/QueryVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/RenderDeviceVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/RenderPassVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/SamplerVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/ShaderBindingTableVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/ShaderResourceBindingVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/ShaderVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/SwapChainVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/TextureViewVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/TextureVk.h>
    #include <Graphics/GraphicsEngineVulkan/interface/TopLevelASVk.h>
#endif

// OpenGL factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB
    #include <Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>
#endif

// OpenGL native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB) && (__has_include(<GL/glcorearb.h>) || __has_include(<GL/gl.h>) || __has_include(<GLES3/gl3.h>) || __has_include(<OpenGL/gl3.h>) || __has_include(<OpenGLES/ES3/gl.h>))
    #if PLATFORM_WIN32
        #include <windows.h>
    #endif
    #if __has_include(<GL/glcorearb.h>)
        #include <GL/glcorearb.h>
    #elif __has_include(<GL/gl.h>)
        #include <GL/gl.h>
    #elif __has_include(<GLES3/gl3.h>)
        #include <GLES3/gl3.h>
    #elif __has_include(<OpenGL/gl3.h>)
        #include <OpenGL/gl3.h>
    #else
        #include <OpenGLES/ES3/gl.h>
    #endif
    #include <Graphics/GraphicsEngineOpenGL/interface/BufferGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/BufferViewGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/DeviceContextGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/FenceGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/PipelineStateGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/QueryGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/RenderDeviceGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/SamplerGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/ShaderGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/ShaderResourceBindingGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/SwapChainGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/TextureGL.h>
    #include <Graphics/GraphicsEngineOpenGL/interface/TextureViewGL.h>
#endif

// D3D11 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
    #include <Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h>
#endif

// D3D11 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
// SDK types must precede Diligent interfaces; preserve this include order.

    #include <d3d11.h>
    #include <dxgi1_4.h>

    #include <Graphics/GraphicsEngineD3D11/interface/BufferD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/BufferViewD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/DeviceContextD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/DeviceMemoryD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/FenceD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/PipelineStateD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/QueryD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/RenderDeviceD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/SamplerD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/ShaderD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/ShaderResourceBindingD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/SwapChainD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/TextureD3D11.h>
    #include <Graphics/GraphicsEngineD3D11/interface/TextureViewD3D11.h>
    #include <Graphics/GraphicsEngineD3DBase/interface/ShaderD3D.h>
    #include <Graphics/GraphicsEngineD3DBase/interface/ShaderResourceVariableD3D.h>
#endif

// D3D12 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
    #include <Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h>
#endif

// D3D12 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
// SDK types must precede Diligent interfaces; preserve this include order.

    #include <d3d12.h>
    #include <dxgi1_4.h>

    #include <Graphics/GraphicsEngineD3D12/interface/BottomLevelASD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/BufferD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/BufferViewD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/CommandQueueD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/DeviceContextD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/DeviceMemoryD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/FenceD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/PipelineStateCacheD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/PipelineStateD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/QueryD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/RenderDeviceD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/SamplerD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/ShaderBindingTableD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/ShaderD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/ShaderResourceBindingD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/SwapChainD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/TextureD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/TextureViewD3D12.h>
    #include <Graphics/GraphicsEngineD3D12/interface/TopLevelASD3D12.h>
#endif

// Metal factory
#if PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS
    #include <Graphics/GraphicsEngineMetal/interface/EngineFactoryMtl.h>
#endif

// Metal native interfaces
#if (PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS) && defined(__OBJC__)
// SDK types must precede Diligent interfaces; preserve this include order.

    #import <Metal/Metal.h>

    #include <Graphics/GraphicsEngineMetal/interface/BottomLevelASMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/BufferMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/BufferViewMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/CommandQueueMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/DeviceContextMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/DeviceMemoryMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/FenceMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/PipelineStateCacheMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/PipelineStateMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/QueryMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/RasterizationRateMapMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/RenderDeviceMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/SamplerMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/ShaderMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/ShaderResourceBindingMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/SwapChainMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/TextureMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/TextureViewMtl.h>
    #include <Graphics/GraphicsEngineMetal/interface/TopLevelASMtl.h>
#endif

export module ModdersDream.Renderer.Diligent;

export namespace ModdersDream::Renderer::Diligent {

// Reference-counted ownership.
template <typename T>
using RefCntAutoPtr = ::Diligent::RefCntAutoPtr<T>;

template <typename T>
using RefCntWeakPtr = ::Diligent::RefCntWeakPtr<T>;

// Native window and asynchronous compilation.
using NativeWindow = ::Diligent::NativeWindow;
using AsyncTaskStatus = ::Diligent::ASYNC_TASK_STATUS;
using IAsyncTask = ::Diligent::IAsyncTask;
using IThreadPool = ::Diligent::IThreadPool;

// BasicTypes
using Float32 = ::Diligent::Float32;
using Float64 = ::Diligent::Float64;
using Int64 = ::Diligent::Int64;
using Int32 = ::Diligent::Int32;
using Int16 = ::Diligent::Int16;
using Int8 = ::Diligent::Int8;
using Uint64 = ::Diligent::Uint64;
using Uint32 = ::Diligent::Uint32;
using Uint16 = ::Diligent::Uint16;
using Uint8 = ::Diligent::Uint8;
using SizeType = ::Diligent::SizeType;
using PVoid = ::Diligent::PVoid;
using CpVoid = ::Diligent::CPVoid;
using Bool = ::Diligent::Bool;
using Char = ::Diligent::Char;
using String = ::Diligent::String;

// InterfaceID
using InterfaceId = ::Diligent::INTERFACE_ID;

// Object
using IObject = ::Diligent::IObject;

// ReferenceCounters
using ReferenceCounterValueType = ::Diligent::ReferenceCounterValueType;
using IReferenceCounters = ::Diligent::IReferenceCounters;

// MemoryAllocator
using IMemoryAllocator = ::Diligent::IMemoryAllocator;

// DataBlob
using IDataBlob = ::Diligent::IDataBlob;

// FileStream
using IFileStream = ::Diligent::IFileStream;

// DebugOutput
using DebugMessageSeverity = ::Diligent::DEBUG_MESSAGE_SEVERITY;
using enum DebugMessageSeverity;
using DebugMessageCallbackType = ::Diligent::DebugMessageCallbackType;

// ApiInfo
using ApiInfo = ::Diligent::APIInfo;

// BlendState
using BlendFactor = ::Diligent::BLEND_FACTOR;
using BlendOperation = ::Diligent::BLEND_OPERATION;
using ColorMask = ::Diligent::COLOR_MASK;
using LogicOperation = ::Diligent::LOGIC_OPERATION;
using RenderTargetBlendDesc = ::Diligent::RenderTargetBlendDesc;
using BlendStateDesc = ::Diligent::BlendStateDesc;

// BottomLevelAS
using BlasTriangleDesc = ::Diligent::BLASTriangleDesc;
using BlasBoundingBoxDesc = ::Diligent::BLASBoundingBoxDesc;
using RaytracingBuildAsFlags = ::Diligent::RAYTRACING_BUILD_AS_FLAGS;
using BottomLevelAsDesc = ::Diligent::BottomLevelASDesc;
using ScratchBufferSizes = ::Diligent::ScratchBufferSizes;
using IBottomLevelAs = ::Diligent::IBottomLevelAS;

// Buffer
using BufferMode = ::Diligent::BUFFER_MODE;
using MiscBufferFlags = ::Diligent::MISC_BUFFER_FLAGS;
using BufferDesc = ::Diligent::BufferDesc;
using BufferData = ::Diligent::BufferData;
using SparseBufferProperties = ::Diligent::SparseBufferProperties;
using IBuffer = ::Diligent::IBuffer;

// BufferView
using BufferFormat = ::Diligent::BufferFormat;
using BufferViewDesc = ::Diligent::BufferViewDesc;
using IBufferView = ::Diligent::IBufferView;

// CommandList
using ICommandList = ::Diligent::ICommandList;

// CommandQueue
using ICommandQueue = ::Diligent::ICommandQueue;

// Dearchiver
using ShaderUnpackInfo = ::Diligent::ShaderUnpackInfo;
using ResourceSignatureUnpackInfo = ::Diligent::ResourceSignatureUnpackInfo;
using PsoArchiveFlags = ::Diligent::PSO_ARCHIVE_FLAGS;
using PsoUnpackFlags = ::Diligent::PSO_UNPACK_FLAGS;
using PipelineStateUnpackInfo = ::Diligent::PipelineStateUnpackInfo;
using RenderPassUnpackInfo = ::Diligent::RenderPassUnpackInfo;
using IDearchiver = ::Diligent::IDearchiver;

// DepthStencilState
using StencilOp = ::Diligent::STENCIL_OP;
using StencilOpDesc = ::Diligent::StencilOpDesc;
using DepthStencilStateDesc = ::Diligent::DepthStencilStateDesc;

// DeviceContext
using DeviceContextDesc = ::Diligent::DeviceContextDesc;
using DrawFlags = ::Diligent::DRAW_FLAGS;
using ResourceStateTransitionMode = ::Diligent::RESOURCE_STATE_TRANSITION_MODE;
using DrawAttribs = ::Diligent::DrawAttribs;
using DrawIndexedAttribs = ::Diligent::DrawIndexedAttribs;
using DrawIndirectAttribs = ::Diligent::DrawIndirectAttribs;
using DrawIndexedIndirectAttribs = ::Diligent::DrawIndexedIndirectAttribs;
using DrawMeshAttribsMtl = ::Diligent::DrawMeshAttribsMtl;
using DrawMeshAttribs = ::Diligent::DrawMeshAttribs;
using DrawMeshIndirectAttribs = ::Diligent::DrawMeshIndirectAttribs;
using MultiDrawItem = ::Diligent::MultiDrawItem;
using MultiDrawAttribs = ::Diligent::MultiDrawAttribs;
using MultiDrawIndexedItem = ::Diligent::MultiDrawIndexedItem;
using MultiDrawIndexedAttribs = ::Diligent::MultiDrawIndexedAttribs;
using ClearDepthStencilFlags = ::Diligent::CLEAR_DEPTH_STENCIL_FLAGS;
using DispatchComputeAttribs = ::Diligent::DispatchComputeAttribs;
using DispatchComputeIndirectAttribs = ::Diligent::DispatchComputeIndirectAttribs;
using DispatchTileAttribs = ::Diligent::DispatchTileAttribs;
using ResolveTextureSubresourceAttribs = ::Diligent::ResolveTextureSubresourceAttribs;
using SetVertexBuffersFlags = ::Diligent::SET_VERTEX_BUFFERS_FLAGS;
using Viewport = ::Diligent::Viewport;
using Rect = ::Diligent::Rect;
using CopyTextureAttribs = ::Diligent::CopyTextureAttribs;
using SetRenderTargetsAttribs = ::Diligent::SetRenderTargetsAttribs;
using BeginRenderPassAttribs = ::Diligent::BeginRenderPassAttribs;
using RaytracingInstanceFlags = ::Diligent::RAYTRACING_INSTANCE_FLAGS;
using CopyAsMode = ::Diligent::COPY_AS_MODE;
using RaytracingGeometryFlags = ::Diligent::RAYTRACING_GEOMETRY_FLAGS;
using BlasBuildTriangleData = ::Diligent::BLASBuildTriangleData;
using BlasBuildBoundingBoxData = ::Diligent::BLASBuildBoundingBoxData;
using BuildBlasAttribs = ::Diligent::BuildBLASAttribs;
using InstanceMatrix = ::Diligent::InstanceMatrix;
using TlasBuildInstanceData = ::Diligent::TLASBuildInstanceData;
using BuildTlasAttribs = ::Diligent::BuildTLASAttribs;
using CopyBlasAttribs = ::Diligent::CopyBLASAttribs;
using CopyTlasAttribs = ::Diligent::CopyTLASAttribs;
using WriteBlasCompactedSizeAttribs = ::Diligent::WriteBLASCompactedSizeAttribs;
using WriteTlasCompactedSizeAttribs = ::Diligent::WriteTLASCompactedSizeAttribs;
using TraceRaysAttribs = ::Diligent::TraceRaysAttribs;
using TraceRaysIndirectAttribs = ::Diligent::TraceRaysIndirectAttribs;
using UpdateIndirectRtBufferAttribs = ::Diligent::UpdateIndirectRTBufferAttribs;
using SparseBufferMemoryBindRange = ::Diligent::SparseBufferMemoryBindRange;
using SparseBufferMemoryBindInfo = ::Diligent::SparseBufferMemoryBindInfo;
using SparseTextureMemoryBindRange = ::Diligent::SparseTextureMemoryBindRange;
using SparseTextureMemoryBindInfo = ::Diligent::SparseTextureMemoryBindInfo;
using BindSparseResourceMemoryAttribs = ::Diligent::BindSparseResourceMemoryAttribs;
using StateTransitionFlags = ::Diligent::STATE_TRANSITION_FLAGS;
using StateTransitionDesc = ::Diligent::StateTransitionDesc;
using DeviceContextCommandCounters = ::Diligent::DeviceContextCommandCounters;
using DeviceContextStats = ::Diligent::DeviceContextStats;
using IDeviceContext = ::Diligent::IDeviceContext;

// DeviceMemory
using DeviceMemoryType = ::Diligent::DEVICE_MEMORY_TYPE;
using DeviceMemoryDesc = ::Diligent::DeviceMemoryDesc;
using DeviceMemoryCreateInfo = ::Diligent::DeviceMemoryCreateInfo;
using IDeviceMemory = ::Diligent::IDeviceMemory;

// DeviceObject
using IDeviceObject = ::Diligent::IDeviceObject;

// EngineFactory
using IShaderSourceInputStreamFactory = ::Diligent::IShaderSourceInputStreamFactory;
using DearchiverCreateInfo = ::Diligent::DearchiverCreateInfo;
using IEngineFactory = ::Diligent::IEngineFactory;

// Fence
using FenceType = ::Diligent::FENCE_TYPE;
using FenceDesc = ::Diligent::FenceDesc;
using IFence = ::Diligent::IFence;

// Framebuffer
using FramebufferDesc = ::Diligent::FramebufferDesc;
using IFramebuffer = ::Diligent::IFramebuffer;

// GraphicsTypes
using ValueType = ::Diligent::VALUE_TYPE;
using ShaderType = ::Diligent::SHADER_TYPE;
using BindFlags = ::Diligent::BIND_FLAGS;
using Usage = ::Diligent::USAGE;
using CpuAccessFlags = ::Diligent::CPU_ACCESS_FLAGS;
using MapType = ::Diligent::MAP_TYPE;
using MapFlags = ::Diligent::MAP_FLAGS;
using ResourceDimension = ::Diligent::RESOURCE_DIMENSION;
using TextureViewType = ::Diligent::TEXTURE_VIEW_TYPE;
using BufferViewType = ::Diligent::BUFFER_VIEW_TYPE;
using TextureFormat = ::Diligent::TEXTURE_FORMAT;
using FilterType = ::Diligent::FILTER_TYPE;
using TextureAddressMode = ::Diligent::TEXTURE_ADDRESS_MODE;
using ComparisonFunction = ::Diligent::COMPARISON_FUNCTION;
using PrimitiveTopology = ::Diligent::PRIMITIVE_TOPOLOGY;
using MemoryProperties = ::Diligent::MEMORY_PROPERTIES;
using DepthStencilClearValue = ::Diligent::DepthStencilClearValue;
using OptimizedClearValue = ::Diligent::OptimizedClearValue;
using DeviceObjectAttribs = ::Diligent::DeviceObjectAttribs;
using AdapterType = ::Diligent::ADAPTER_TYPE;
using ScalingMode = ::Diligent::SCALING_MODE;
using ScanlineOrder = ::Diligent::SCANLINE_ORDER;
using DisplayModeAttribs = ::Diligent::DisplayModeAttribs;
using SwapChainUsageFlags = ::Diligent::SWAP_CHAIN_USAGE_FLAGS;
using SurfaceTransform = ::Diligent::SURFACE_TRANSFORM;
using SwapChainDesc = ::Diligent::SwapChainDesc;
using FullScreenModeDesc = ::Diligent::FullScreenModeDesc;
using QueryType = ::Diligent::QUERY_TYPE;
using RenderDeviceType = ::Diligent::RENDER_DEVICE_TYPE;
using DeviceFeatureState = ::Diligent::DEVICE_FEATURE_STATE;
using DeviceFeatures = ::Diligent::DeviceFeatures;
using AdapterVendor = ::Diligent::ADAPTER_VENDOR;
using Version = ::Diligent::Version;
using WaveFeature = ::Diligent::WAVE_FEATURE;
using ValidationLevel = ::Diligent::VALIDATION_LEVEL;
using TextureProperties = ::Diligent::TextureProperties;
using SamplerProperties = ::Diligent::SamplerProperties;
using WaveOpProperties = ::Diligent::WaveOpProperties;
using BufferProperties = ::Diligent::BufferProperties;
using RayTracingCapFlags = ::Diligent::RAY_TRACING_CAP_FLAGS;
using RayTracingProperties = ::Diligent::RayTracingProperties;
using MeshShaderProperties = ::Diligent::MeshShaderProperties;
using ComputeShaderProperties = ::Diligent::ComputeShaderProperties;
using NdcAttribs = ::Diligent::NDCAttribs;
using RenderDeviceShaderVersionInfo = ::Diligent::RenderDeviceShaderVersionInfo;
using RenderDeviceInfo = ::Diligent::RenderDeviceInfo;
using ValidationFlags = ::Diligent::VALIDATION_FLAGS;
using CommandQueueType = ::Diligent::COMMAND_QUEUE_TYPE;
using QueuePriority = ::Diligent::QUEUE_PRIORITY;
using AdapterMemoryInfo = ::Diligent::AdapterMemoryInfo;
using ShadingRateCombiner = ::Diligent::SHADING_RATE_COMBINER;
using ShadingRateFormat = ::Diligent::SHADING_RATE_FORMAT;
using AxisShadingRate = ::Diligent::AXIS_SHADING_RATE;
using ShadingRate = ::Diligent::SHADING_RATE;
using SampleCount = ::Diligent::SAMPLE_COUNT;
using ShadingRateMode = ::Diligent::ShadingRateMode;
using ShadingRateCapFlags = ::Diligent::SHADING_RATE_CAP_FLAGS;
using ShadingRateTextureAccess = ::Diligent::SHADING_RATE_TEXTURE_ACCESS;
using ShadingRateProperties = ::Diligent::ShadingRateProperties;
using DrawCommandCapFlags = ::Diligent::DRAW_COMMAND_CAP_FLAGS;
using DrawCommandProperties = ::Diligent::DrawCommandProperties;
using SparseResourceCapFlags = ::Diligent::SPARSE_RESOURCE_CAP_FLAGS;
using SparseResourceProperties = ::Diligent::SparseResourceProperties;
using CommandQueueInfo = ::Diligent::CommandQueueInfo;
using GraphicsAdapterInfo = ::Diligent::GraphicsAdapterInfo;
using ImmediateContextCreateInfo = ::Diligent::ImmediateContextCreateInfo;
using OpenXrAttribs = ::Diligent::OpenXRAttribs;
using EngineCreateInfo = ::Diligent::EngineCreateInfo;
using EngineGlCreateInfo = ::Diligent::EngineGLCreateInfo;
using D3d11ValidationFlags = ::Diligent::D3D11_VALIDATION_FLAGS;
using EngineD3d11CreateInfo = ::Diligent::EngineD3D11CreateInfo;
using D3d12ValidationFlags = ::Diligent::D3D12_VALIDATION_FLAGS;
using EngineD3d12CreateInfo = ::Diligent::EngineD3D12CreateInfo;
using VulkanDescriptorPoolSize = ::Diligent::VulkanDescriptorPoolSize;
using DeviceFeaturesVk = ::Diligent::DeviceFeaturesVk;
using EngineVkCreateInfo = ::Diligent::EngineVkCreateInfo;
using EngineMtlCreateInfo = ::Diligent::EngineMtlCreateInfo;
using EngineWebGpuCreateInfo = ::Diligent::EngineWebGPUCreateInfo;
using Box = ::Diligent::Box;
using ComponentType = ::Diligent::COMPONENT_TYPE;
using TextureFormatAttribs = ::Diligent::TextureFormatAttribs;
using TextureFormatInfo = ::Diligent::TextureFormatInfo;
using ResourceDimensionSupport = ::Diligent::RESOURCE_DIMENSION_SUPPORT;
using TextureFormatInfoExt = ::Diligent::TextureFormatInfoExt;
using SparseTextureFlags = ::Diligent::SPARSE_TEXTURE_FLAGS;
using SparseTextureFormatInfo = ::Diligent::SparseTextureFormatInfo;
using PipelineStageFlags = ::Diligent::PIPELINE_STAGE_FLAGS;
using AccessFlags = ::Diligent::ACCESS_FLAGS;
using ResourceState = ::Diligent::RESOURCE_STATE;
using StateTransitionType = ::Diligent::STATE_TRANSITION_TYPE;

// InputLayout
using InputElementFrequency = ::Diligent::INPUT_ELEMENT_FREQUENCY;
using LayoutElement = ::Diligent::LayoutElement;
using InputLayoutDesc = ::Diligent::InputLayoutDesc;

// PipelineResourceSignature
using ImmutableSamplerDesc = ::Diligent::ImmutableSamplerDesc;
using PipelineResourceFlags = ::Diligent::PIPELINE_RESOURCE_FLAGS;
using WebGpuBindingType = ::Diligent::WEB_GPU_BINDING_TYPE;
using WebGpuResourceAttribs = ::Diligent::WebGPUResourceAttribs;
using PipelineResourceDesc = ::Diligent::PipelineResourceDesc;
using PipelineResourceSignatureDesc = ::Diligent::PipelineResourceSignatureDesc;
using IPipelineResourceSignature = ::Diligent::IPipelineResourceSignature;

// PipelineState
using SampleDesc = ::Diligent::SampleDesc;
using ShaderVariableFlags = ::Diligent::SHADER_VARIABLE_FLAGS;
using ShaderResourceVariableDesc = ::Diligent::ShaderResourceVariableDesc;
using PipelineShadingRateFlags = ::Diligent::PIPELINE_SHADING_RATE_FLAGS;
using PipelineResourceLayoutDesc = ::Diligent::PipelineResourceLayoutDesc;
using GraphicsPipelineDesc = ::Diligent::GraphicsPipelineDesc;
using RayTracingGeneralShaderGroup = ::Diligent::RayTracingGeneralShaderGroup;
using RayTracingTriangleHitShaderGroup = ::Diligent::RayTracingTriangleHitShaderGroup;
using RayTracingProceduralHitShaderGroup = ::Diligent::RayTracingProceduralHitShaderGroup;
using RayTracingPipelineDesc = ::Diligent::RayTracingPipelineDesc;
using PipelineType = ::Diligent::PIPELINE_TYPE;
using PipelineStateDesc = ::Diligent::PipelineStateDesc;
using PsoCreateFlags = ::Diligent::PSO_CREATE_FLAGS;
using SpecializationConstant = ::Diligent::SpecializationConstant;
using PipelineStateCreateInfo = ::Diligent::PipelineStateCreateInfo;
using GraphicsPipelineStateCreateInfo = ::Diligent::GraphicsPipelineStateCreateInfo;
using ComputePipelineStateCreateInfo = ::Diligent::ComputePipelineStateCreateInfo;
using RayTracingPipelineStateCreateInfo = ::Diligent::RayTracingPipelineStateCreateInfo;
using TilePipelineDesc = ::Diligent::TilePipelineDesc;
using TilePipelineStateCreateInfo = ::Diligent::TilePipelineStateCreateInfo;
using PipelineStateStatus = ::Diligent::PIPELINE_STATE_STATUS;
using IPipelineState = ::Diligent::IPipelineState;

// PipelineStateCache
using PsoCacheMode = ::Diligent::PSO_CACHE_MODE;
using PsoCacheFlags = ::Diligent::PSO_CACHE_FLAGS;
using PipelineStateCacheDesc = ::Diligent::PipelineStateCacheDesc;
using PipelineStateCacheCreateInfo = ::Diligent::PipelineStateCacheCreateInfo;
using IPipelineStateCache = ::Diligent::IPipelineStateCache;

// Query
using QueryDataOcclusion = ::Diligent::QueryDataOcclusion;
using QueryDataBinaryOcclusion = ::Diligent::QueryDataBinaryOcclusion;
using QueryDataTimestamp = ::Diligent::QueryDataTimestamp;
using QueryDataPipelineStatistics = ::Diligent::QueryDataPipelineStatistics;
using QueryDataDuration = ::Diligent::QueryDataDuration;
using QueryDesc = ::Diligent::QueryDesc;
using IQuery = ::Diligent::IQuery;

// RasterizerState
using FillMode = ::Diligent::FILL_MODE;
using CullMode = ::Diligent::CULL_MODE;
using RasterizerStateDesc = ::Diligent::RasterizerStateDesc;

// RenderDevice
using IRenderDevice = ::Diligent::IRenderDevice;

// RenderPass
using AttachmentLoadOp = ::Diligent::ATTACHMENT_LOAD_OP;
using AttachmentStoreOp = ::Diligent::ATTACHMENT_STORE_OP;
using RenderPassAttachmentDesc = ::Diligent::RenderPassAttachmentDesc;
using AttachmentReference = ::Diligent::AttachmentReference;
using ShadingRateAttachment = ::Diligent::ShadingRateAttachment;
using SubpassDesc = ::Diligent::SubpassDesc;
using SubpassDependencyDesc = ::Diligent::SubpassDependencyDesc;
using RenderPassDesc = ::Diligent::RenderPassDesc;
using IRenderPass = ::Diligent::IRenderPass;

// ResourceMapping
using ResourceMappingEntry = ::Diligent::ResourceMappingEntry;
using ResourceMappingCreateInfo = ::Diligent::ResourceMappingCreateInfo;
using IResourceMapping = ::Diligent::IResourceMapping;

// Sampler
using SamplerFlags = ::Diligent::SAMPLER_FLAGS;
using SamplerDesc = ::Diligent::SamplerDesc;
using ISampler = ::Diligent::ISampler;

// Shader
using ShaderVersion = ::Diligent::ShaderVersion;
using ShaderSourceLanguage = ::Diligent::SHADER_SOURCE_LANGUAGE;
using ShaderCompiler = ::Diligent::SHADER_COMPILER;
using CreateShaderSourceInputStreamFlags = ::Diligent::CREATE_SHADER_SOURCE_INPUT_STREAM_FLAGS;
using ShaderDesc = ::Diligent::ShaderDesc;
using ShaderStatus = ::Diligent::SHADER_STATUS;
using ShaderMacro = ::Diligent::ShaderMacro;
using ShaderMacroArray = ::Diligent::ShaderMacroArray;
using ShaderCompileFlags = ::Diligent::SHADER_COMPILE_FLAGS;
using ShaderOptimizationLevel = ::Diligent::SHADER_OPTIMIZATION_LEVEL;
using ShaderCreateInfo = ::Diligent::ShaderCreateInfo;
using ShaderResourceType = ::Diligent::SHADER_RESOURCE_TYPE;
using ShaderResourceDesc = ::Diligent::ShaderResourceDesc;
using ShaderCodeBasicType = ::Diligent::SHADER_CODE_BASIC_TYPE;
using ShaderCodeVariableClass = ::Diligent::SHADER_CODE_VARIABLE_CLASS;
using IShader = ::Diligent::IShader;

// ShaderBindingTable
using ShaderBindingTableDesc = ::Diligent::ShaderBindingTableDesc;
using VerifySbtFlags = ::Diligent::VERIFY_SBT_FLAGS;
using IShaderBindingTable = ::Diligent::IShaderBindingTable;

// ShaderResourceBinding
using IShaderResourceBinding = ::Diligent::IShaderResourceBinding;

// ShaderResourceVariable
using ShaderResourceVariableType = ::Diligent::SHADER_RESOURCE_VARIABLE_TYPE;
using ShaderResourceVariableTypeFlags = ::Diligent::SHADER_RESOURCE_VARIABLE_TYPE_FLAGS;
using BindShaderResourcesFlags = ::Diligent::BIND_SHADER_RESOURCES_FLAGS;
using SetShaderResourceFlags = ::Diligent::SET_SHADER_RESOURCE_FLAGS;
using IShaderResourceVariable = ::Diligent::IShaderResourceVariable;

// SwapChain
using ISwapChain = ::Diligent::ISwapChain;

// Texture
using MiscTextureFlags = ::Diligent::MISC_TEXTURE_FLAGS;
using TextureDesc = ::Diligent::TextureDesc;
using TextureSubResData = ::Diligent::TextureSubResData;
using TextureData = ::Diligent::TextureData;
using MappedTextureSubresource = ::Diligent::MappedTextureSubresource;
using SparseTextureProperties = ::Diligent::SparseTextureProperties;
using ITexture = ::Diligent::ITexture;

// TextureView
using UavAccessFlag = ::Diligent::UAV_ACCESS_FLAG;
using TextureViewFlags = ::Diligent::TEXTURE_VIEW_FLAGS;
using TextureComponentSwizzle = ::Diligent::TEXTURE_COMPONENT_SWIZZLE;
using TextureComponentMapping = ::Diligent::TextureComponentMapping;
using TextureViewDesc = ::Diligent::TextureViewDesc;
using ITextureView = ::Diligent::ITextureView;

// TopLevelAS
using TopLevelAsDesc = ::Diligent::TopLevelASDesc;
using HitGroupBindingMode = ::Diligent::HIT_GROUP_BINDING_MODE;
using TlasBuildInfo = ::Diligent::TLASBuildInfo;
using TlasInstanceDesc = ::Diligent::TLASInstanceDesc;
using ITopLevelAs = ::Diligent::ITopLevelAS;

// GraphicsTypesX
using SubpassDescX = ::Diligent::SubpassDescX;
using RenderPassDescX = ::Diligent::RenderPassDescX;
using InputLayoutDescX = ::Diligent::InputLayoutDescX;
template <typename DerivedType, typename BaseType>
using DeviceObjectAttribsX = ::Diligent::DeviceObjectAttribsX<DerivedType, BaseType>;
using FramebufferDescX = ::Diligent::FramebufferDescX;
using PipelineResourceSignatureDescX = ::Diligent::PipelineResourceSignatureDescX;
using PipelineResourceLayoutDescX = ::Diligent::PipelineResourceLayoutDescX;
using BottomLevelAsDescX = ::Diligent::BottomLevelASDescX;
template <typename DerivedType, typename CreateInfoType>
using PipelineStateCreateInfoX = ::Diligent::PipelineStateCreateInfoX<DerivedType, CreateInfoType>;
using GraphicsPipelineStateCreateInfoX = ::Diligent::GraphicsPipelineStateCreateInfoX;
using ComputePipelineStateCreateInfoX = ::Diligent::ComputePipelineStateCreateInfoX;
using TilePipelineStateCreateInfoX = ::Diligent::TilePipelineStateCreateInfoX;
using RayTracingPipelineStateCreateInfoX = ::Diligent::RayTracingPipelineStateCreateInfoX;
template <typename T>
using PipelineStateCreateInfoXTraits = ::Diligent::PipelineStateCreateInfoXTraits<T>;
template <bool ThrowOnError = true>
using RenderDeviceX = ::Diligent::RenderDeviceX<ThrowOnError>;
using RenderDeviceXE = ::Diligent::RenderDeviceX_E;
using RenderDeviceXN = ::Diligent::RenderDeviceX_N;
using ShaderResourceVariableX = ::Diligent::ShaderResourceVariableX;
using MultiDrawAttribsX = ::Diligent::MultiDrawAttribsX;
using MultiDrawIndexedAttribsX = ::Diligent::MultiDrawIndexedAttribsX;

// Vulkan factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS
using IEngineFactoryVk = ::Diligent::IEngineFactoryVk;
using GetEngineFactoryVkType = ::Diligent::GetEngineFactoryVkType;
using ::Diligent::LoadAndGetEngineFactoryVk;
    #if DILIGENT_VK_EXPLICIT_LOAD
using ::Diligent::LoadGraphicsEngineVk;
    #else
using ::Diligent::GetEngineFactoryVk;
    #endif
#endif

// Vulkan native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS) && __has_include(<vulkan/vulkan.h>)
using IBottomLevelAsVk = ::Diligent::IBottomLevelASVk;
using IBufferViewVk = ::Diligent::IBufferViewVk;
using IBufferVk = ::Diligent::IBufferVk;
using ICommandQueueVk = ::Diligent::ICommandQueueVk;
using IDeviceContextVk = ::Diligent::IDeviceContextVk;
using DeviceMemoryRangeVk = ::Diligent::DeviceMemoryRangeVk;
using IDeviceMemoryVk = ::Diligent::IDeviceMemoryVk;
using IFenceVk = ::Diligent::IFenceVk;
using IFramebufferVk = ::Diligent::IFramebufferVk;
using IPipelineStateCacheVk = ::Diligent::IPipelineStateCacheVk;
using IPipelineStateVk = ::Diligent::IPipelineStateVk;
using IQueryVk = ::Diligent::IQueryVk;
using IRenderDeviceVk = ::Diligent::IRenderDeviceVk;
using IRenderPassVk = ::Diligent::IRenderPassVk;
using ISamplerVk = ::Diligent::ISamplerVk;
using BindingTableVk = ::Diligent::BindingTableVk;
using IShaderBindingTableVk = ::Diligent::IShaderBindingTableVk;
using IShaderResourceBindingVk = ::Diligent::IShaderResourceBindingVk;
using IShaderVk = ::Diligent::IShaderVk;
using ISwapChainVk = ::Diligent::ISwapChainVk;
using ITextureViewVk = ::Diligent::ITextureViewVk;
using ITextureVk = ::Diligent::ITextureVk;
using ITopLevelAsVk = ::Diligent::ITopLevelASVk;
#endif

// OpenGL factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB
using IEngineFactoryOpenGl = ::Diligent::IEngineFactoryOpenGL;
using GetEngineFactoryOpenGlType = ::Diligent::GetEngineFactoryOpenGLType;
using ::Diligent::LoadAndGetEngineFactoryOpenGL;
    #if DILIGENT_OPENGL_EXPLICIT_LOAD
using ::Diligent::LoadGraphicsEngineOpenGL;
    #else
using ::Diligent::GetEngineFactoryOpenGL;
    #endif
#endif

// OpenGL native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB) && (__has_include(<GL/glcorearb.h>) || __has_include(<GL/gl.h>) || __has_include(<GLES3/gl3.h>) || __has_include(<OpenGL/gl3.h>) || __has_include(<OpenGLES/ES3/gl.h>))
using IBufferGl = ::Diligent::IBufferGL;
using IBufferViewGl = ::Diligent::IBufferViewGL;
using IDeviceContextGl = ::Diligent::IDeviceContextGL;
using IFenceGl = ::Diligent::IFenceGL;
using IPipelineStateGl = ::Diligent::IPipelineStateGL;
using IQueryGl = ::Diligent::IQueryGL;
    #if PLATFORM_WIN32
using NativeGlContextAttribsWin32 = ::Diligent::NativeGLContextAttribsWin32;
    #elif PLATFORM_ANDROID
using NativeGlContextAttribsAndroid = ::Diligent::NativeGLContextAttribsAndroid;
    #endif
    #if PLATFORM_WIN32 || PLATFORM_ANDROID
using NativeGlContextAttribs = ::Diligent::NativeGLContextAttribs;
    #endif
using IRenderDeviceGl = ::Diligent::IRenderDeviceGL;
using ISamplerGl = ::Diligent::ISamplerGL;
using IShaderGl = ::Diligent::IShaderGL;
using IShaderResourceBindingGl = ::Diligent::IShaderResourceBindingGL;
using ISwapChainGl = ::Diligent::ISwapChainGL;
using ITextureGl = ::Diligent::ITextureGL;
using ITextureViewGl = ::Diligent::ITextureViewGL;
#endif

// D3D11 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IEngineFactoryD3d11 = ::Diligent::IEngineFactoryD3D11;
using GetEngineFactoryD3d11Type = ::Diligent::GetEngineFactoryD3D11Type;
using ::Diligent::LoadAndGetEngineFactoryD3D11;
    #if DILIGENT_D3D11_SHARED
using ::Diligent::LoadGraphicsEngineD3D11;
    #else
using ::Diligent::GetEngineFactoryD3D11;
    #endif
#endif

// D3D11 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using HlslShaderResourceDesc = ::Diligent::HLSLShaderResourceDesc;
using IShaderD3d = ::Diligent::IShaderD3D;
using IShaderResourceVariableD3d = ::Diligent::IShaderResourceVariableD3D;
using IBufferD3d11 = ::Diligent::IBufferD3D11;
using IBufferViewD3d11 = ::Diligent::IBufferViewD3D11;
using IDeviceContextD3d11 = ::Diligent::IDeviceContextD3D11;
using IDeviceMemoryD3d11 = ::Diligent::IDeviceMemoryD3D11;
using IFenceD3d11 = ::Diligent::IFenceD3D11;
using IPipelineStateD3d11 = ::Diligent::IPipelineStateD3D11;
using IQueryD3d11 = ::Diligent::IQueryD3D11;
using IRenderDeviceD3d11 = ::Diligent::IRenderDeviceD3D11;
using ISamplerD3d11 = ::Diligent::ISamplerD3D11;
using IShaderD3d11 = ::Diligent::IShaderD3D11;
using IShaderResourceBindingD3d11 = ::Diligent::IShaderResourceBindingD3D11;
using ISwapChainD3d11 = ::Diligent::ISwapChainD3D11;
using ITextureD3d11 = ::Diligent::ITextureD3D11;
using ITextureViewD3d11 = ::Diligent::ITextureViewD3D11;
#endif

// D3D12 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IEngineFactoryD3d12 = ::Diligent::IEngineFactoryD3D12;
using GetEngineFactoryD3d12Type = ::Diligent::GetEngineFactoryD3D12Type;
using ::Diligent::LoadAndGetEngineFactoryD3D12;
    #if DILIGENT_D3D12_SHARED
using ::Diligent::LoadGraphicsEngineD3D12;
    #else
using ::Diligent::GetEngineFactoryD3D12;
    #endif
#endif

// D3D12 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IBottomLevelAsD3d12 = ::Diligent::IBottomLevelASD3D12;
using IBufferD3d12 = ::Diligent::IBufferD3D12;
using IBufferViewD3d12 = ::Diligent::IBufferViewD3D12;
using ResourceTileMappingsD3d12 = ::Diligent::ResourceTileMappingsD3D12;
using ICommandQueueD3d12 = ::Diligent::ICommandQueueD3D12;
using IDeviceContextD3d12 = ::Diligent::IDeviceContextD3D12;
using DeviceMemoryRangeD3d12 = ::Diligent::DeviceMemoryRangeD3D12;
using IDeviceMemoryD3d12 = ::Diligent::IDeviceMemoryD3D12;
using IFenceD3d12 = ::Diligent::IFenceD3D12;
using IPipelineStateCacheD3d12 = ::Diligent::IPipelineStateCacheD3D12;
using IPipelineStateD3d12 = ::Diligent::IPipelineStateD3D12;
using IQueryD3d12 = ::Diligent::IQueryD3D12;
using IRenderDeviceD3d12 = ::Diligent::IRenderDeviceD3D12;
using ISamplerD3d12 = ::Diligent::ISamplerD3D12;
using IShaderBindingTableD3d12 = ::Diligent::IShaderBindingTableD3D12;
using IShaderD3d12 = ::Diligent::IShaderD3D12;
using IShaderResourceBindingD3d12 = ::Diligent::IShaderResourceBindingD3D12;
using ISwapChainD3d12 = ::Diligent::ISwapChainD3D12;
using ITextureD3d12 = ::Diligent::ITextureD3D12;
using ITextureViewD3d12 = ::Diligent::ITextureViewD3D12;
using ITopLevelAsD3d12 = ::Diligent::ITopLevelASD3D12;
#endif

// Metal factory
#if PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS
using IEngineFactoryMtl = ::Diligent::IEngineFactoryMtl;
using ::Diligent::GetEngineFactoryMtl;
#endif

// Metal native interfaces
#if (PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS) && defined(__OBJC__)
using IBottomLevelAsMtl = ::Diligent::IBottomLevelASMtl;
using IBufferMtl = ::Diligent::IBufferMtl;
using IBufferViewMtl = ::Diligent::IBufferViewMtl;
using ICommandQueueMtl = ::Diligent::ICommandQueueMtl;
using IDeviceContextMtl = ::Diligent::IDeviceContextMtl;
using IDeviceMemoryMtl = ::Diligent::IDeviceMemoryMtl;
using IFenceMtl = ::Diligent::IFenceMtl;
using IPipelineStateCacheMtl = ::Diligent::IPipelineStateCacheMtl;
using IPipelineStateMtl = ::Diligent::IPipelineStateMtl;
using IQueryMtl = ::Diligent::IQueryMtl;
using RasterizationRateMapDesc = ::Diligent::RasterizationRateMapDesc;
using RasterizationRateLayerDesc = ::Diligent::RasterizationRateLayerDesc;
using RasterizationRateMapCreateInfo = ::Diligent::RasterizationRateMapCreateInfo;
using IRasterizationRateMapMtl = ::Diligent::IRasterizationRateMapMtl;
using IRenderDeviceMtl = ::Diligent::IRenderDeviceMtl;
using ISamplerMtl = ::Diligent::ISamplerMtl;
using IShaderMtl = ::Diligent::IShaderMtl;
using IShaderResourceBindingMtl = ::Diligent::IShaderResourceBindingMtl;
using ISwapChainMtl = ::Diligent::ISwapChainMtl;
using ITextureMtl = ::Diligent::ITextureMtl;
using ITextureViewMtl = ::Diligent::ITextureViewMtl;
using ITopLevelAsMtl = ::Diligent::ITopLevelASMtl;
#endif

} // namespace ModdersDream::Renderer::Diligent
