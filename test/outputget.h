#define boundaryField "{\n\
    processor\n\
    {\n\
        type            processor;\n\
        value           uniform 0.24;\n\
    }\n\
    motorBikeGroup\n\
    {\n\
        type            kqRWallFunction;\n\
        value           uniform 0.24;\n\
    }\n\
}"

#define cascadedField "{\n\
    type test;\n\
    inlet\n\
    {\n\
      type test2;\n\
    }\n\
  }"

#define motorBikeGroup "{\n\
        type            kqRWallFunction;\n\
        value           uniform 0.24;\n\
    }"
