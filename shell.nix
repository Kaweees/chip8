{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang # C++ compiler
    cppcheck # C++ linter
    cmake # CMake build system
    cmake-format # CMake format tool
    nixfmt # Nix formatter
    just # Just runner
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
    xorg.libXext
    mesa
    libGL
  ];

  # Shell hook to set up environment
  shellHook = ''
    export LD_LIBRARY_PATH=${
      pkgs.lib.makeLibraryPath [
        pkgs.xorg.libX11
        pkgs.xorg.libXrandr
        pkgs.xorg.libXinerama
        pkgs.xorg.libXcursor
        pkgs.xorg.libXi
        pkgs.xorg.libXext
        pkgs.libGL
        pkgs.mesa
      ]
    }:$LD_LIBRARY_PATH
  '';
}
