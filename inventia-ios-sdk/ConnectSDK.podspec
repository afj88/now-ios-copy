#
#  Be sure to run `pod spec lint ConnectSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|
  s.name         = "ConnectSDK"
  s.version      = "3.0.9"
  s.summary      = "ConnectSDK iOS Static Library."
  s.description  = <<-DESC
                  ConnectSDK iOS Static Library
                   DESC
  s.homepage     = "http://www.inventia.biz"
  s.author  = { "Inventia" => "info@inventia.biz" }
  s.source = { :path => "." }
  s.source_files  = "include/*.h"
  s.public_header_files = "include/*.h"
  s.preserve_paths = "libConnectSDK.a"
  s.resource = "ConnectSDK.bundle"
  s.ios.vendored_library = "libConnectSDK.a"
  s.frameworks = "Foundation", "AVFoundation", "GLKit", "VideoToolbox", "MobileCoreServices", "AssetsLibrary"
  s.libraries = "c++", "icucore"
  s.requires_arc = true
  s.xcconfig = { 'OTHER_LDFLAGS' => '$(inherited)' }
end
