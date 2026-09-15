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
    // clang-format off
    #include <vulkan/vulkan.h>
    // clang-format on

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
    // clang-format off
    #include <d3d11.h>
    #include <dxgi1_4.h>
    // clang-format on

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
    // clang-format off
    #include <d3d12.h>
    #include <dxgi1_4.h>
    // clang-format on

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
    // clang-format off
    #import <Metal/Metal.h>
    // clang-format on

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

export module md.renderer.diligent;

export namespace md::renderer::diligent {

// Reference-counted ownership.
template <typename T>
using RefCntAutoPtr = Diligent::RefCntAutoPtr<T>;

template <typename T>
using RefCntWeakPtr = Diligent::RefCntWeakPtr<T>;

// Native window and asynchronous compilation.
using NativeWindow = Diligent::NativeWindow;
using ASYNC_TASK_STATUS = Diligent::ASYNC_TASK_STATUS;
using IAsyncTask = Diligent::IAsyncTask;
using IThreadPool = Diligent::IThreadPool;

// BasicTypes
using Float32 = Diligent::Float32;
using Float64 = Diligent::Float64;
using Int64 = Diligent::Int64;
using Int32 = Diligent::Int32;
using Int16 = Diligent::Int16;
using Int8 = Diligent::Int8;
using Uint64 = Diligent::Uint64;
using Uint32 = Diligent::Uint32;
using Uint16 = Diligent::Uint16;
using Uint8 = Diligent::Uint8;
using SizeType = Diligent::SizeType;
using PVoid = Diligent::PVoid;
using CPVoid = Diligent::CPVoid;
using Bool = Diligent::Bool;
using Char = Diligent::Char;
using String = Diligent::String;

// InterfaceID
using INTERFACE_ID = Diligent::INTERFACE_ID;

// Object
using IObject = Diligent::IObject;

// ReferenceCounters
using ReferenceCounterValueType = Diligent::ReferenceCounterValueType;
using IReferenceCounters = Diligent::IReferenceCounters;

// MemoryAllocator
using IMemoryAllocator = Diligent::IMemoryAllocator;

// DataBlob
using IDataBlob = Diligent::IDataBlob;

// FileStream
using IFileStream = Diligent::IFileStream;

// DebugOutput
using DEBUG_MESSAGE_SEVERITY = Diligent::DEBUG_MESSAGE_SEVERITY;
using DebugMessageCallbackType = Diligent::DebugMessageCallbackType;

// APIInfo
using APIInfo = Diligent::APIInfo;

// BlendState
using BLEND_FACTOR = Diligent::BLEND_FACTOR;
using BLEND_OPERATION = Diligent::BLEND_OPERATION;
using COLOR_MASK = Diligent::COLOR_MASK;
using LOGIC_OPERATION = Diligent::LOGIC_OPERATION;
using RenderTargetBlendDesc = Diligent::RenderTargetBlendDesc;
using BlendStateDesc = Diligent::BlendStateDesc;

// BottomLevelAS
using BLASTriangleDesc = Diligent::BLASTriangleDesc;
using BLASBoundingBoxDesc = Diligent::BLASBoundingBoxDesc;
using RAYTRACING_BUILD_AS_FLAGS = Diligent::RAYTRACING_BUILD_AS_FLAGS;
using BottomLevelASDesc = Diligent::BottomLevelASDesc;
using ScratchBufferSizes = Diligent::ScratchBufferSizes;
using IBottomLevelAS = Diligent::IBottomLevelAS;

// Buffer
using BUFFER_MODE = Diligent::BUFFER_MODE;
using MISC_BUFFER_FLAGS = Diligent::MISC_BUFFER_FLAGS;
using BufferDesc = Diligent::BufferDesc;
using BufferData = Diligent::BufferData;
using SparseBufferProperties = Diligent::SparseBufferProperties;
using IBuffer = Diligent::IBuffer;

// BufferView
using BufferFormat = Diligent::BufferFormat;
using BufferViewDesc = Diligent::BufferViewDesc;
using IBufferView = Diligent::IBufferView;

// CommandList
using ICommandList = Diligent::ICommandList;

// CommandQueue
using ICommandQueue = Diligent::ICommandQueue;

// Dearchiver
using ShaderUnpackInfo = Diligent::ShaderUnpackInfo;
using ResourceSignatureUnpackInfo = Diligent::ResourceSignatureUnpackInfo;
using PSO_ARCHIVE_FLAGS = Diligent::PSO_ARCHIVE_FLAGS;
using PSO_UNPACK_FLAGS = Diligent::PSO_UNPACK_FLAGS;
using PipelineStateUnpackInfo = Diligent::PipelineStateUnpackInfo;
using RenderPassUnpackInfo = Diligent::RenderPassUnpackInfo;
using IDearchiver = Diligent::IDearchiver;

// DepthStencilState
using STENCIL_OP = Diligent::STENCIL_OP;
using StencilOpDesc = Diligent::StencilOpDesc;
using DepthStencilStateDesc = Diligent::DepthStencilStateDesc;

// DeviceContext
using DeviceContextDesc = Diligent::DeviceContextDesc;
using DRAW_FLAGS = Diligent::DRAW_FLAGS;
using RESOURCE_STATE_TRANSITION_MODE = Diligent::RESOURCE_STATE_TRANSITION_MODE;
using DrawAttribs = Diligent::DrawAttribs;
using DrawIndexedAttribs = Diligent::DrawIndexedAttribs;
using DrawIndirectAttribs = Diligent::DrawIndirectAttribs;
using DrawIndexedIndirectAttribs = Diligent::DrawIndexedIndirectAttribs;
using DrawMeshAttribsMtl = Diligent::DrawMeshAttribsMtl;
using DrawMeshAttribs = Diligent::DrawMeshAttribs;
using DrawMeshIndirectAttribs = Diligent::DrawMeshIndirectAttribs;
using MultiDrawItem = Diligent::MultiDrawItem;
using MultiDrawAttribs = Diligent::MultiDrawAttribs;
using MultiDrawIndexedItem = Diligent::MultiDrawIndexedItem;
using MultiDrawIndexedAttribs = Diligent::MultiDrawIndexedAttribs;
using CLEAR_DEPTH_STENCIL_FLAGS = Diligent::CLEAR_DEPTH_STENCIL_FLAGS;
using DispatchComputeAttribs = Diligent::DispatchComputeAttribs;
using DispatchComputeIndirectAttribs = Diligent::DispatchComputeIndirectAttribs;
using DispatchTileAttribs = Diligent::DispatchTileAttribs;
using ResolveTextureSubresourceAttribs = Diligent::ResolveTextureSubresourceAttribs;
using SET_VERTEX_BUFFERS_FLAGS = Diligent::SET_VERTEX_BUFFERS_FLAGS;
using Viewport = Diligent::Viewport;
using Rect = Diligent::Rect;
using CopyTextureAttribs = Diligent::CopyTextureAttribs;
using SetRenderTargetsAttribs = Diligent::SetRenderTargetsAttribs;
using BeginRenderPassAttribs = Diligent::BeginRenderPassAttribs;
using RAYTRACING_INSTANCE_FLAGS = Diligent::RAYTRACING_INSTANCE_FLAGS;
using COPY_AS_MODE = Diligent::COPY_AS_MODE;
using RAYTRACING_GEOMETRY_FLAGS = Diligent::RAYTRACING_GEOMETRY_FLAGS;
using BLASBuildTriangleData = Diligent::BLASBuildTriangleData;
using BLASBuildBoundingBoxData = Diligent::BLASBuildBoundingBoxData;
using BuildBLASAttribs = Diligent::BuildBLASAttribs;
using InstanceMatrix = Diligent::InstanceMatrix;
using TLASBuildInstanceData = Diligent::TLASBuildInstanceData;
using BuildTLASAttribs = Diligent::BuildTLASAttribs;
using CopyBLASAttribs = Diligent::CopyBLASAttribs;
using CopyTLASAttribs = Diligent::CopyTLASAttribs;
using WriteBLASCompactedSizeAttribs = Diligent::WriteBLASCompactedSizeAttribs;
using WriteTLASCompactedSizeAttribs = Diligent::WriteTLASCompactedSizeAttribs;
using TraceRaysAttribs = Diligent::TraceRaysAttribs;
using TraceRaysIndirectAttribs = Diligent::TraceRaysIndirectAttribs;
using UpdateIndirectRTBufferAttribs = Diligent::UpdateIndirectRTBufferAttribs;
using SparseBufferMemoryBindRange = Diligent::SparseBufferMemoryBindRange;
using SparseBufferMemoryBindInfo = Diligent::SparseBufferMemoryBindInfo;
using SparseTextureMemoryBindRange = Diligent::SparseTextureMemoryBindRange;
using SparseTextureMemoryBindInfo = Diligent::SparseTextureMemoryBindInfo;
using BindSparseResourceMemoryAttribs = Diligent::BindSparseResourceMemoryAttribs;
using STATE_TRANSITION_FLAGS = Diligent::STATE_TRANSITION_FLAGS;
using StateTransitionDesc = Diligent::StateTransitionDesc;
using DeviceContextCommandCounters = Diligent::DeviceContextCommandCounters;
using DeviceContextStats = Diligent::DeviceContextStats;
using IDeviceContext = Diligent::IDeviceContext;

// DeviceMemory
using DEVICE_MEMORY_TYPE = Diligent::DEVICE_MEMORY_TYPE;
using DeviceMemoryDesc = Diligent::DeviceMemoryDesc;
using DeviceMemoryCreateInfo = Diligent::DeviceMemoryCreateInfo;
using IDeviceMemory = Diligent::IDeviceMemory;

// DeviceObject
using IDeviceObject = Diligent::IDeviceObject;

// EngineFactory
using IShaderSourceInputStreamFactory = Diligent::IShaderSourceInputStreamFactory;
using DearchiverCreateInfo = Diligent::DearchiverCreateInfo;
using IEngineFactory = Diligent::IEngineFactory;

// Fence
using FENCE_TYPE = Diligent::FENCE_TYPE;
using FenceDesc = Diligent::FenceDesc;
using IFence = Diligent::IFence;

// Framebuffer
using FramebufferDesc = Diligent::FramebufferDesc;
using IFramebuffer = Diligent::IFramebuffer;

// GraphicsTypes
using VALUE_TYPE = Diligent::VALUE_TYPE;
using SHADER_TYPE = Diligent::SHADER_TYPE;
using BIND_FLAGS = Diligent::BIND_FLAGS;
using USAGE = Diligent::USAGE;
using CPU_ACCESS_FLAGS = Diligent::CPU_ACCESS_FLAGS;
using MAP_TYPE = Diligent::MAP_TYPE;
using MAP_FLAGS = Diligent::MAP_FLAGS;
using RESOURCE_DIMENSION = Diligent::RESOURCE_DIMENSION;
using TEXTURE_VIEW_TYPE = Diligent::TEXTURE_VIEW_TYPE;
using BUFFER_VIEW_TYPE = Diligent::BUFFER_VIEW_TYPE;
using TEXTURE_FORMAT = Diligent::TEXTURE_FORMAT;
using FILTER_TYPE = Diligent::FILTER_TYPE;
using TEXTURE_ADDRESS_MODE = Diligent::TEXTURE_ADDRESS_MODE;
using COMPARISON_FUNCTION = Diligent::COMPARISON_FUNCTION;
using PRIMITIVE_TOPOLOGY = Diligent::PRIMITIVE_TOPOLOGY;
using MEMORY_PROPERTIES = Diligent::MEMORY_PROPERTIES;
using DepthStencilClearValue = Diligent::DepthStencilClearValue;
using OptimizedClearValue = Diligent::OptimizedClearValue;
using DeviceObjectAttribs = Diligent::DeviceObjectAttribs;
using ADAPTER_TYPE = Diligent::ADAPTER_TYPE;
using SCALING_MODE = Diligent::SCALING_MODE;
using SCANLINE_ORDER = Diligent::SCANLINE_ORDER;
using DisplayModeAttribs = Diligent::DisplayModeAttribs;
using SWAP_CHAIN_USAGE_FLAGS = Diligent::SWAP_CHAIN_USAGE_FLAGS;
using SURFACE_TRANSFORM = Diligent::SURFACE_TRANSFORM;
using SwapChainDesc = Diligent::SwapChainDesc;
using FullScreenModeDesc = Diligent::FullScreenModeDesc;
using QUERY_TYPE = Diligent::QUERY_TYPE;
using RENDER_DEVICE_TYPE = Diligent::RENDER_DEVICE_TYPE;
using DEVICE_FEATURE_STATE = Diligent::DEVICE_FEATURE_STATE;
using DeviceFeatures = Diligent::DeviceFeatures;
using ADAPTER_VENDOR = Diligent::ADAPTER_VENDOR;
using Version = Diligent::Version;
using WAVE_FEATURE = Diligent::WAVE_FEATURE;
using VALIDATION_LEVEL = Diligent::VALIDATION_LEVEL;
using TextureProperties = Diligent::TextureProperties;
using SamplerProperties = Diligent::SamplerProperties;
using WaveOpProperties = Diligent::WaveOpProperties;
using BufferProperties = Diligent::BufferProperties;
using RAY_TRACING_CAP_FLAGS = Diligent::RAY_TRACING_CAP_FLAGS;
using RayTracingProperties = Diligent::RayTracingProperties;
using MeshShaderProperties = Diligent::MeshShaderProperties;
using ComputeShaderProperties = Diligent::ComputeShaderProperties;
using NDCAttribs = Diligent::NDCAttribs;
using RenderDeviceShaderVersionInfo = Diligent::RenderDeviceShaderVersionInfo;
using RenderDeviceInfo = Diligent::RenderDeviceInfo;
using VALIDATION_FLAGS = Diligent::VALIDATION_FLAGS;
using COMMAND_QUEUE_TYPE = Diligent::COMMAND_QUEUE_TYPE;
using QUEUE_PRIORITY = Diligent::QUEUE_PRIORITY;
using AdapterMemoryInfo = Diligent::AdapterMemoryInfo;
using SHADING_RATE_COMBINER = Diligent::SHADING_RATE_COMBINER;
using SHADING_RATE_FORMAT = Diligent::SHADING_RATE_FORMAT;
using AXIS_SHADING_RATE = Diligent::AXIS_SHADING_RATE;
using SHADING_RATE = Diligent::SHADING_RATE;
using SAMPLE_COUNT = Diligent::SAMPLE_COUNT;
using ShadingRateMode = Diligent::ShadingRateMode;
using SHADING_RATE_CAP_FLAGS = Diligent::SHADING_RATE_CAP_FLAGS;
using SHADING_RATE_TEXTURE_ACCESS = Diligent::SHADING_RATE_TEXTURE_ACCESS;
using ShadingRateProperties = Diligent::ShadingRateProperties;
using DRAW_COMMAND_CAP_FLAGS = Diligent::DRAW_COMMAND_CAP_FLAGS;
using DrawCommandProperties = Diligent::DrawCommandProperties;
using SPARSE_RESOURCE_CAP_FLAGS = Diligent::SPARSE_RESOURCE_CAP_FLAGS;
using SparseResourceProperties = Diligent::SparseResourceProperties;
using CommandQueueInfo = Diligent::CommandQueueInfo;
using GraphicsAdapterInfo = Diligent::GraphicsAdapterInfo;
using ImmediateContextCreateInfo = Diligent::ImmediateContextCreateInfo;
using OpenXRAttribs = Diligent::OpenXRAttribs;
using EngineCreateInfo = Diligent::EngineCreateInfo;
using EngineGLCreateInfo = Diligent::EngineGLCreateInfo;
using D3D11_VALIDATION_FLAGS = Diligent::D3D11_VALIDATION_FLAGS;
using EngineD3D11CreateInfo = Diligent::EngineD3D11CreateInfo;
using D3D12_VALIDATION_FLAGS = Diligent::D3D12_VALIDATION_FLAGS;
using EngineD3D12CreateInfo = Diligent::EngineD3D12CreateInfo;
using VulkanDescriptorPoolSize = Diligent::VulkanDescriptorPoolSize;
using DeviceFeaturesVk = Diligent::DeviceFeaturesVk;
using EngineVkCreateInfo = Diligent::EngineVkCreateInfo;
using EngineMtlCreateInfo = Diligent::EngineMtlCreateInfo;
using EngineWebGPUCreateInfo = Diligent::EngineWebGPUCreateInfo;
using Box = Diligent::Box;
using COMPONENT_TYPE = Diligent::COMPONENT_TYPE;
using TextureFormatAttribs = Diligent::TextureFormatAttribs;
using TextureFormatInfo = Diligent::TextureFormatInfo;
using RESOURCE_DIMENSION_SUPPORT = Diligent::RESOURCE_DIMENSION_SUPPORT;
using TextureFormatInfoExt = Diligent::TextureFormatInfoExt;
using SPARSE_TEXTURE_FLAGS = Diligent::SPARSE_TEXTURE_FLAGS;
using SparseTextureFormatInfo = Diligent::SparseTextureFormatInfo;
using PIPELINE_STAGE_FLAGS = Diligent::PIPELINE_STAGE_FLAGS;
using ACCESS_FLAGS = Diligent::ACCESS_FLAGS;
using RESOURCE_STATE = Diligent::RESOURCE_STATE;
using STATE_TRANSITION_TYPE = Diligent::STATE_TRANSITION_TYPE;

// InputLayout
using INPUT_ELEMENT_FREQUENCY = Diligent::INPUT_ELEMENT_FREQUENCY;
using LayoutElement = Diligent::LayoutElement;
using InputLayoutDesc = Diligent::InputLayoutDesc;

// PipelineResourceSignature
using ImmutableSamplerDesc = Diligent::ImmutableSamplerDesc;
using PIPELINE_RESOURCE_FLAGS = Diligent::PIPELINE_RESOURCE_FLAGS;
using WEB_GPU_BINDING_TYPE = Diligent::WEB_GPU_BINDING_TYPE;
using WebGPUResourceAttribs = Diligent::WebGPUResourceAttribs;
using PipelineResourceDesc = Diligent::PipelineResourceDesc;
using PipelineResourceSignatureDesc = Diligent::PipelineResourceSignatureDesc;
using IPipelineResourceSignature = Diligent::IPipelineResourceSignature;

// PipelineState
using SampleDesc = Diligent::SampleDesc;
using SHADER_VARIABLE_FLAGS = Diligent::SHADER_VARIABLE_FLAGS;
using ShaderResourceVariableDesc = Diligent::ShaderResourceVariableDesc;
using PIPELINE_SHADING_RATE_FLAGS = Diligent::PIPELINE_SHADING_RATE_FLAGS;
using PipelineResourceLayoutDesc = Diligent::PipelineResourceLayoutDesc;
using GraphicsPipelineDesc = Diligent::GraphicsPipelineDesc;
using RayTracingGeneralShaderGroup = Diligent::RayTracingGeneralShaderGroup;
using RayTracingTriangleHitShaderGroup = Diligent::RayTracingTriangleHitShaderGroup;
using RayTracingProceduralHitShaderGroup = Diligent::RayTracingProceduralHitShaderGroup;
using RayTracingPipelineDesc = Diligent::RayTracingPipelineDesc;
using PIPELINE_TYPE = Diligent::PIPELINE_TYPE;
using PipelineStateDesc = Diligent::PipelineStateDesc;
using PSO_CREATE_FLAGS = Diligent::PSO_CREATE_FLAGS;
using SpecializationConstant = Diligent::SpecializationConstant;
using PipelineStateCreateInfo = Diligent::PipelineStateCreateInfo;
using GraphicsPipelineStateCreateInfo = Diligent::GraphicsPipelineStateCreateInfo;
using ComputePipelineStateCreateInfo = Diligent::ComputePipelineStateCreateInfo;
using RayTracingPipelineStateCreateInfo = Diligent::RayTracingPipelineStateCreateInfo;
using TilePipelineDesc = Diligent::TilePipelineDesc;
using TilePipelineStateCreateInfo = Diligent::TilePipelineStateCreateInfo;
using PIPELINE_STATE_STATUS = Diligent::PIPELINE_STATE_STATUS;
using IPipelineState = Diligent::IPipelineState;

// PipelineStateCache
using PSO_CACHE_MODE = Diligent::PSO_CACHE_MODE;
using PSO_CACHE_FLAGS = Diligent::PSO_CACHE_FLAGS;
using PipelineStateCacheDesc = Diligent::PipelineStateCacheDesc;
using PipelineStateCacheCreateInfo = Diligent::PipelineStateCacheCreateInfo;
using IPipelineStateCache = Diligent::IPipelineStateCache;

// Query
using QueryDataOcclusion = Diligent::QueryDataOcclusion;
using QueryDataBinaryOcclusion = Diligent::QueryDataBinaryOcclusion;
using QueryDataTimestamp = Diligent::QueryDataTimestamp;
using QueryDataPipelineStatistics = Diligent::QueryDataPipelineStatistics;
using QueryDataDuration = Diligent::QueryDataDuration;
using QueryDesc = Diligent::QueryDesc;
using IQuery = Diligent::IQuery;

// RasterizerState
using FILL_MODE = Diligent::FILL_MODE;
using CULL_MODE = Diligent::CULL_MODE;
using RasterizerStateDesc = Diligent::RasterizerStateDesc;

// RenderDevice
using IRenderDevice = Diligent::IRenderDevice;

// RenderPass
using ATTACHMENT_LOAD_OP = Diligent::ATTACHMENT_LOAD_OP;
using ATTACHMENT_STORE_OP = Diligent::ATTACHMENT_STORE_OP;
using RenderPassAttachmentDesc = Diligent::RenderPassAttachmentDesc;
using AttachmentReference = Diligent::AttachmentReference;
using ShadingRateAttachment = Diligent::ShadingRateAttachment;
using SubpassDesc = Diligent::SubpassDesc;
using SubpassDependencyDesc = Diligent::SubpassDependencyDesc;
using RenderPassDesc = Diligent::RenderPassDesc;
using IRenderPass = Diligent::IRenderPass;

// ResourceMapping
using ResourceMappingEntry = Diligent::ResourceMappingEntry;
using ResourceMappingCreateInfo = Diligent::ResourceMappingCreateInfo;
using IResourceMapping = Diligent::IResourceMapping;

// Sampler
using SAMPLER_FLAGS = Diligent::SAMPLER_FLAGS;
using SamplerDesc = Diligent::SamplerDesc;
using ISampler = Diligent::ISampler;

// Shader
using ShaderVersion = Diligent::ShaderVersion;
using SHADER_SOURCE_LANGUAGE = Diligent::SHADER_SOURCE_LANGUAGE;
using SHADER_COMPILER = Diligent::SHADER_COMPILER;
using CREATE_SHADER_SOURCE_INPUT_STREAM_FLAGS = Diligent::CREATE_SHADER_SOURCE_INPUT_STREAM_FLAGS;
using ShaderDesc = Diligent::ShaderDesc;
using SHADER_STATUS = Diligent::SHADER_STATUS;
using ShaderMacro = Diligent::ShaderMacro;
using ShaderMacroArray = Diligent::ShaderMacroArray;
using SHADER_COMPILE_FLAGS = Diligent::SHADER_COMPILE_FLAGS;
using SHADER_OPTIMIZATION_LEVEL = Diligent::SHADER_OPTIMIZATION_LEVEL;
using ShaderCreateInfo = Diligent::ShaderCreateInfo;
using SHADER_RESOURCE_TYPE = Diligent::SHADER_RESOURCE_TYPE;
using ShaderResourceDesc = Diligent::ShaderResourceDesc;
using SHADER_CODE_BASIC_TYPE = Diligent::SHADER_CODE_BASIC_TYPE;
using SHADER_CODE_VARIABLE_CLASS = Diligent::SHADER_CODE_VARIABLE_CLASS;
using IShader = Diligent::IShader;

// ShaderBindingTable
using ShaderBindingTableDesc = Diligent::ShaderBindingTableDesc;
using VERIFY_SBT_FLAGS = Diligent::VERIFY_SBT_FLAGS;
using IShaderBindingTable = Diligent::IShaderBindingTable;

// ShaderResourceBinding
using IShaderResourceBinding = Diligent::IShaderResourceBinding;

// ShaderResourceVariable
using SHADER_RESOURCE_VARIABLE_TYPE = Diligent::SHADER_RESOURCE_VARIABLE_TYPE;
using SHADER_RESOURCE_VARIABLE_TYPE_FLAGS = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_FLAGS;
using BIND_SHADER_RESOURCES_FLAGS = Diligent::BIND_SHADER_RESOURCES_FLAGS;
using SET_SHADER_RESOURCE_FLAGS = Diligent::SET_SHADER_RESOURCE_FLAGS;
using IShaderResourceVariable = Diligent::IShaderResourceVariable;

// SwapChain
using ISwapChain = Diligent::ISwapChain;

// Texture
using MISC_TEXTURE_FLAGS = Diligent::MISC_TEXTURE_FLAGS;
using TextureDesc = Diligent::TextureDesc;
using TextureSubResData = Diligent::TextureSubResData;
using TextureData = Diligent::TextureData;
using MappedTextureSubresource = Diligent::MappedTextureSubresource;
using SparseTextureProperties = Diligent::SparseTextureProperties;
using ITexture = Diligent::ITexture;

// TextureView
using UAV_ACCESS_FLAG = Diligent::UAV_ACCESS_FLAG;
using TEXTURE_VIEW_FLAGS = Diligent::TEXTURE_VIEW_FLAGS;
using TEXTURE_COMPONENT_SWIZZLE = Diligent::TEXTURE_COMPONENT_SWIZZLE;
using TextureComponentMapping = Diligent::TextureComponentMapping;
using TextureViewDesc = Diligent::TextureViewDesc;
using ITextureView = Diligent::ITextureView;

// TopLevelAS
using TopLevelASDesc = Diligent::TopLevelASDesc;
using HIT_GROUP_BINDING_MODE = Diligent::HIT_GROUP_BINDING_MODE;
using TLASBuildInfo = Diligent::TLASBuildInfo;
using TLASInstanceDesc = Diligent::TLASInstanceDesc;
using ITopLevelAS = Diligent::ITopLevelAS;

// GraphicsTypesX
using SubpassDescX = Diligent::SubpassDescX;
using RenderPassDescX = Diligent::RenderPassDescX;
using InputLayoutDescX = Diligent::InputLayoutDescX;
template <typename DerivedType, typename BaseType>
using DeviceObjectAttribsX = Diligent::DeviceObjectAttribsX<DerivedType, BaseType>;
using FramebufferDescX = Diligent::FramebufferDescX;
using PipelineResourceSignatureDescX = Diligent::PipelineResourceSignatureDescX;
using PipelineResourceLayoutDescX = Diligent::PipelineResourceLayoutDescX;
using BottomLevelASDescX = Diligent::BottomLevelASDescX;
template <typename DerivedType, typename CreateInfoType>
using PipelineStateCreateInfoX = Diligent::PipelineStateCreateInfoX<DerivedType, CreateInfoType>;
using GraphicsPipelineStateCreateInfoX = Diligent::GraphicsPipelineStateCreateInfoX;
using ComputePipelineStateCreateInfoX = Diligent::ComputePipelineStateCreateInfoX;
using TilePipelineStateCreateInfoX = Diligent::TilePipelineStateCreateInfoX;
using RayTracingPipelineStateCreateInfoX = Diligent::RayTracingPipelineStateCreateInfoX;
template <typename T>
using PipelineStateCreateInfoXTraits = Diligent::PipelineStateCreateInfoXTraits<T>;
template <bool ThrowOnError = true>
using RenderDeviceX = Diligent::RenderDeviceX<ThrowOnError>;
using RenderDeviceX_E = Diligent::RenderDeviceX_E;
using RenderDeviceX_N = Diligent::RenderDeviceX_N;
using ShaderResourceVariableX = Diligent::ShaderResourceVariableX;
using MultiDrawAttribsX = Diligent::MultiDrawAttribsX;
using MultiDrawIndexedAttribsX = Diligent::MultiDrawIndexedAttribsX;

// Vulkan factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS
using IEngineFactoryVk = Diligent::IEngineFactoryVk;
using GetEngineFactoryVkType = Diligent::GetEngineFactoryVkType;
using Diligent::LoadAndGetEngineFactoryVk;
    #if DILIGENT_VK_EXPLICIT_LOAD
using Diligent::LoadGraphicsEngineVk;
    #else
using Diligent::GetEngineFactoryVk;
    #endif
#endif

// Vulkan native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS) && __has_include(<vulkan/vulkan.h>)
using IBottomLevelASVk = Diligent::IBottomLevelASVk;
using IBufferViewVk = Diligent::IBufferViewVk;
using IBufferVk = Diligent::IBufferVk;
using ICommandQueueVk = Diligent::ICommandQueueVk;
using IDeviceContextVk = Diligent::IDeviceContextVk;
using DeviceMemoryRangeVk = Diligent::DeviceMemoryRangeVk;
using IDeviceMemoryVk = Diligent::IDeviceMemoryVk;
using IFenceVk = Diligent::IFenceVk;
using IFramebufferVk = Diligent::IFramebufferVk;
using IPipelineStateCacheVk = Diligent::IPipelineStateCacheVk;
using IPipelineStateVk = Diligent::IPipelineStateVk;
using IQueryVk = Diligent::IQueryVk;
using IRenderDeviceVk = Diligent::IRenderDeviceVk;
using IRenderPassVk = Diligent::IRenderPassVk;
using ISamplerVk = Diligent::ISamplerVk;
using BindingTableVk = Diligent::BindingTableVk;
using IShaderBindingTableVk = Diligent::IShaderBindingTableVk;
using IShaderResourceBindingVk = Diligent::IShaderResourceBindingVk;
using IShaderVk = Diligent::IShaderVk;
using ISwapChainVk = Diligent::ISwapChainVk;
using ITextureViewVk = Diligent::ITextureViewVk;
using ITextureVk = Diligent::ITextureVk;
using ITopLevelASVk = Diligent::ITopLevelASVk;
#endif

// OpenGL factory
#if PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB
using IEngineFactoryOpenGL = Diligent::IEngineFactoryOpenGL;
using GetEngineFactoryOpenGLType = Diligent::GetEngineFactoryOpenGLType;
using Diligent::LoadAndGetEngineFactoryOpenGL;
    #if DILIGENT_OPENGL_EXPLICIT_LOAD
using Diligent::LoadGraphicsEngineOpenGL;
    #else
using Diligent::GetEngineFactoryOpenGL;
    #endif
#endif

// OpenGL native interfaces
#if (PLATFORM_WIN32 || PLATFORM_ANDROID || PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_WEB) && (__has_include(<GL/glcorearb.h>) || __has_include(<GL/gl.h>) || __has_include(<GLES3/gl3.h>) || __has_include(<OpenGL/gl3.h>) || __has_include(<OpenGLES/ES3/gl.h>))
using IBufferGL = Diligent::IBufferGL;
using IBufferViewGL = Diligent::IBufferViewGL;
using IDeviceContextGL = Diligent::IDeviceContextGL;
using IFenceGL = Diligent::IFenceGL;
using IPipelineStateGL = Diligent::IPipelineStateGL;
using IQueryGL = Diligent::IQueryGL;
    #if PLATFORM_WIN32
using NativeGLContextAttribsWin32 = Diligent::NativeGLContextAttribsWin32;
    #elif PLATFORM_ANDROID
using NativeGLContextAttribsAndroid = Diligent::NativeGLContextAttribsAndroid;
    #endif
    #if PLATFORM_WIN32 || PLATFORM_ANDROID
using NativeGLContextAttribs = Diligent::NativeGLContextAttribs;
    #endif
using IRenderDeviceGL = Diligent::IRenderDeviceGL;
using ISamplerGL = Diligent::ISamplerGL;
using IShaderGL = Diligent::IShaderGL;
using IShaderResourceBindingGL = Diligent::IShaderResourceBindingGL;
using ISwapChainGL = Diligent::ISwapChainGL;
using ITextureGL = Diligent::ITextureGL;
using ITextureViewGL = Diligent::ITextureViewGL;
#endif

// D3D11 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IEngineFactoryD3D11 = Diligent::IEngineFactoryD3D11;
using GetEngineFactoryD3D11Type = Diligent::GetEngineFactoryD3D11Type;
using Diligent::LoadAndGetEngineFactoryD3D11;
    #if DILIGENT_D3D11_SHARED
using Diligent::LoadGraphicsEngineD3D11;
    #else
using Diligent::GetEngineFactoryD3D11;
    #endif
#endif

// D3D11 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using HLSLShaderResourceDesc = Diligent::HLSLShaderResourceDesc;
using IShaderD3D = Diligent::IShaderD3D;
using IShaderResourceVariableD3D = Diligent::IShaderResourceVariableD3D;
using IBufferD3D11 = Diligent::IBufferD3D11;
using IBufferViewD3D11 = Diligent::IBufferViewD3D11;
using IDeviceContextD3D11 = Diligent::IDeviceContextD3D11;
using IDeviceMemoryD3D11 = Diligent::IDeviceMemoryD3D11;
using IFenceD3D11 = Diligent::IFenceD3D11;
using IPipelineStateD3D11 = Diligent::IPipelineStateD3D11;
using IQueryD3D11 = Diligent::IQueryD3D11;
using IRenderDeviceD3D11 = Diligent::IRenderDeviceD3D11;
using ISamplerD3D11 = Diligent::ISamplerD3D11;
using IShaderD3D11 = Diligent::IShaderD3D11;
using IShaderResourceBindingD3D11 = Diligent::IShaderResourceBindingD3D11;
using ISwapChainD3D11 = Diligent::ISwapChainD3D11;
using ITextureD3D11 = Diligent::ITextureD3D11;
using ITextureViewD3D11 = Diligent::ITextureViewD3D11;
#endif

// D3D12 factory
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IEngineFactoryD3D12 = Diligent::IEngineFactoryD3D12;
using GetEngineFactoryD3D12Type = Diligent::GetEngineFactoryD3D12Type;
using Diligent::LoadAndGetEngineFactoryD3D12;
    #if DILIGENT_D3D12_SHARED
using Diligent::LoadGraphicsEngineD3D12;
    #else
using Diligent::GetEngineFactoryD3D12;
    #endif
#endif

// D3D12 native interfaces
#if PLATFORM_WIN32 || PLATFORM_UNIVERSAL_WINDOWS
using IBottomLevelASD3D12 = Diligent::IBottomLevelASD3D12;
using IBufferD3D12 = Diligent::IBufferD3D12;
using IBufferViewD3D12 = Diligent::IBufferViewD3D12;
using ResourceTileMappingsD3D12 = Diligent::ResourceTileMappingsD3D12;
using ICommandQueueD3D12 = Diligent::ICommandQueueD3D12;
using IDeviceContextD3D12 = Diligent::IDeviceContextD3D12;
using DeviceMemoryRangeD3D12 = Diligent::DeviceMemoryRangeD3D12;
using IDeviceMemoryD3D12 = Diligent::IDeviceMemoryD3D12;
using IFenceD3D12 = Diligent::IFenceD3D12;
using IPipelineStateCacheD3D12 = Diligent::IPipelineStateCacheD3D12;
using IPipelineStateD3D12 = Diligent::IPipelineStateD3D12;
using IQueryD3D12 = Diligent::IQueryD3D12;
using IRenderDeviceD3D12 = Diligent::IRenderDeviceD3D12;
using ISamplerD3D12 = Diligent::ISamplerD3D12;
using IShaderBindingTableD3D12 = Diligent::IShaderBindingTableD3D12;
using IShaderD3D12 = Diligent::IShaderD3D12;
using IShaderResourceBindingD3D12 = Diligent::IShaderResourceBindingD3D12;
using ISwapChainD3D12 = Diligent::ISwapChainD3D12;
using ITextureD3D12 = Diligent::ITextureD3D12;
using ITextureViewD3D12 = Diligent::ITextureViewD3D12;
using ITopLevelASD3D12 = Diligent::ITopLevelASD3D12;
#endif

// Metal factory
#if PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS
using IEngineFactoryMtl = Diligent::IEngineFactoryMtl;
using Diligent::GetEngineFactoryMtl;
#endif

// Metal native interfaces
#if (PLATFORM_MACOS || PLATFORM_IOS || PLATFORM_TVOS || PLATFORM_VISIONOS) && defined(__OBJC__)
using IBottomLevelASMtl = Diligent::IBottomLevelASMtl;
using IBufferMtl = Diligent::IBufferMtl;
using IBufferViewMtl = Diligent::IBufferViewMtl;
using ICommandQueueMtl = Diligent::ICommandQueueMtl;
using IDeviceContextMtl = Diligent::IDeviceContextMtl;
using IDeviceMemoryMtl = Diligent::IDeviceMemoryMtl;
using IFenceMtl = Diligent::IFenceMtl;
using IPipelineStateCacheMtl = Diligent::IPipelineStateCacheMtl;
using IPipelineStateMtl = Diligent::IPipelineStateMtl;
using IQueryMtl = Diligent::IQueryMtl;
using RasterizationRateMapDesc = Diligent::RasterizationRateMapDesc;
using RasterizationRateLayerDesc = Diligent::RasterizationRateLayerDesc;
using RasterizationRateMapCreateInfo = Diligent::RasterizationRateMapCreateInfo;
using IRasterizationRateMapMtl = Diligent::IRasterizationRateMapMtl;
using IRenderDeviceMtl = Diligent::IRenderDeviceMtl;
using ISamplerMtl = Diligent::ISamplerMtl;
using IShaderMtl = Diligent::IShaderMtl;
using IShaderResourceBindingMtl = Diligent::IShaderResourceBindingMtl;
using ISwapChainMtl = Diligent::ISwapChainMtl;
using ITextureMtl = Diligent::ITextureMtl;
using ITextureViewMtl = Diligent::ITextureViewMtl;
using ITopLevelASMtl = Diligent::ITopLevelASMtl;
#endif

} // namespace md::renderer::diligent
