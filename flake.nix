{
  description = "Boilerplate Nix Flake";

  # Define dependencies (like the unstable version of nix packages)
  inputs = {          
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      # Supported: Linux Intel / AMD, Linux ARM, MacOS Intel, Apple Silicon MacOS
      supportedArchitectures = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ]; 

      forAllSystems = nixpkgs.lib.genAttrs supportedArchitectures;

      nixpkgsFor = forAllSystems (system: import nixpkgs { 
        inherit system; 
        config.allowUnfree = true; 
      });
      
    in
    {
      devShells = forAllSystems (system:
        let 
          pkgs = nixpkgsFor.${system}; 
          llvm = pkgs.llvmPackages_18;
        in {
          default = nixpkgsFor.${system}.mkShell {
            nativeBuildInputs = [
              llvm.clang-tools    # Needed to expose system headers to clang-tidy
            ];
            buildInputs = [
              pkgs.doxygen
              pkgs.gcc
              pkgs.cmake
              pkgs.gnumake
              pkgs.ninja
              pkgs.pre-commit
              pkgs.valgrind
              pkgs.cppcheck
            ];
            shellHook = ''
              export CC=gcc
              export CXX=g++
            '';
          };
      });
      packages = forAllSystems (system: {
        default = nixpkgsFor.${system}.stdenv.mkDerivation {
          src = ./.;
        };
      });
    };
}
