cmake_minimum_required (VERSION 2.6)
project (ffmpeg)

set(SOURCES
		consumer/ffmpeg_consumer.cpp
		consumer/streaming_consumer.cpp

		producer/audio/audio_decoder.cpp

		producer/filter/audio_filter.cpp
		producer/filter/filter.cpp

		producer/input/input.cpp

		producer/muxer/frame_muxer.cpp

		producer/util/flv.cpp
		producer/util/util.cpp

		producer/video/video_decoder.cpp

		producer/ffmpeg_producer.cpp
		producer/tbb_avcodec.cpp

		audio_channel_remapper.cpp
		ffmpeg.cpp
		ffmpeg_error.cpp
		StdAfx.cpp
)
set(HEADERS
		consumer/ffmpeg_consumer.h
		consumer/streaming_consumer.h

		producer/audio/audio_decoder.h

		producer/filter/audio_filter.h
		producer/filter/filter.h

		producer/input/input.h

		producer/muxer/display_mode.h
		producer/muxer/frame_muxer.h

		producer/util/flv.h
		producer/util/util.h

		producer/video/video_decoder.h

		producer/ffmpeg_producer.h
		producer/tbb_avcodec.h

		ffmpeg.h
		ffmpeg_error.h
		StdAfx.h
)

add_library(ffmpeg ${SOURCES} ${HEADERS})
add_precompiled_header(ffmpeg StdAfx.h FORCEINCLUDE)

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})

set_target_properties(ffmpeg PROPERTIES FOLDER modules)
source_group(sources ./*)
source_group(sources\\consumer consumer/*)
source_group(sources\\producer\\audio producer/audio/*)
source_group(sources\\producer\\filter producer/filter/*)
source_group(sources\\producer\\input producer/input/*)
source_group(sources\\producer\\muxer producer/muxer/*)
source_group(sources\\producer\\util producer/util/*)
source_group(sources\\producer\\video producer/video/*)
source_group(sources\\producer producer/*)

if (MSVC)
	target_link_libraries(ffmpeg
			common
			core

			avformat.lib
			avcodec.lib
			avutil.lib
			avfilter.lib
			avdevice.lib
			swscale.lib
			swresample.lib
	)
else()
	target_link_libraries(ffmpeg
			common
			core

			-Wl,--start-group
			avformat.so
			avcodec.so
			avutil.so
			avfilter.so
			avdevice.so
			swscale.so
			swresample.so
			postproc.so

			ass
			bluray
			crypto
			expat
			fontconfig
			fribidi
			gmp
			gnutls
			gsm
			hogweed
			ilbc
			modplug
			mp3lame
			nettle
			ogg
			opencore-amrnb
			opencore-amrwb
			opus
			rtmp
			ssl
			tasn1
			theoradec
			theoraenc
			vorbis
			vorbisenc
			vpx
			x264
			xavs
			xvidcore
			z
			-Wl,--end-group
	)
endif()

casparcg_add_include_statement("modules/ffmpeg/ffmpeg.h")
casparcg_add_init_statement("ffmpeg::init" "ffmpeg")
casparcg_add_uninit_statement("ffmpeg::uninit")
casparcg_add_module_project("ffmpeg")

if(MSVC)
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/avcodec-57.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/avdevice-57.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/avfilter-6.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/avformat-57.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/avutil-55.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/postproc-54.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/swresample-2.dll")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/swscale-4.dll")
else()
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libavcodec.so.57")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libavdevice.so.57")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libavfilter.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libavformat.so.57")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libavutil.so.55")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libpostproc.so.54")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libswresample.so.2")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libswscale.so.4")

	# 编译
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libass.so.5")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libbluray.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libcrypto.so.10")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libexpat.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libfdk-aac.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libfontconfig.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libfreetype.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libfribidi.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libgme.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libgmp.so.10")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libgnutls.so.28")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libgsm.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libhogweed.so.2")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libilbc.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/liblzma.so.5")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libmodplug.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libmp3lame.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libnettle.so.4")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libogg.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libopencore-amrnb.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libopencore-amrwb.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libopenjpeg.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libopus.so.0")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/liborc-0.4.so")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/liborc-test-0.4.so")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libpcre.so.1")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libpcrecpp.so.0")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libpcreposix.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libpng15.so.15")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/librtmp.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libschroedinger-1.0.so.0")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libsoxr-lsr.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libsoxr.so.0")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libspeex.so.1")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libspeexdsp.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libssl.so.10")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libtasn1.so.6")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libtheora.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libtheoradec.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libtheoraenc.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libtwolame.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libva.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvidstab.so.1.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvo-amrwbenc.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvorbis.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvorbisenc.so.2")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvorbisfile.so.3")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libvpx.so.1")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libwavpack.so.1")
	#casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libwebp.so.4")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libx264.so.148")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libx265.so.79")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libxavs.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libxml2.so.2")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libxvidcore.so.4")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libz.so.1")

	# 最小桌面
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libHalf.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libIex.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libIexMath.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libIlmImf.so.7")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libIlmThread.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libImath.so.6")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libva-drm.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libva-x11.so.1")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libbs2b.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libcaca.so.0")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libglut.so.3")
	casparcg_add_runtime_dependency("${FFMPEG_BIN_PATH}/libmng.so.1")
endif()

