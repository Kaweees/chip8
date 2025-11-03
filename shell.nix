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
  ];

  # Shell hook to set up environment
  shellHook = "";
}
