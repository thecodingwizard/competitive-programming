def Settings(**kwargs):
    return {
        "flags": ["-x", "c++", "-Werror", "-std=c++17"]     # NOTE: supposed to be c++11. Switch to c++11 once migrated to WSL
    }

