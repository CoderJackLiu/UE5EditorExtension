# UE5EditorExtension



## Introduction

This project is a collection of editor extension tools, aimed at extending the Unreal Engine to meet more personalized editor usage requirements and to provide deeper insight into the Unreal Engine editor's source code. The project has multiple branches, each containing different editor extension functionalities, allowing you to choose the appropriate branch based on your needs.

## Features

- **Master Branch**:
  - Serves as the core of the project, summarizing and integrating the functionalities of all branches.
  - Provides a comprehensive ReadMe file, enabling new users to get started quickly.
  - Future updates will include integrations for specific Unreal Engine versions, facilitating developers in selecting the suitable toolset.

- **CustomAssets Branch**:
  - Offers advanced custom FBX asset import tools, capable of automatically converting FBX files into CustomMesh UAssets.
  - Includes innovative menu page extension features, enabling users to easily create CustomMesh assets.
  - Introduces custom viewport and thumbnail rendering features, optimizing asset visualization.
  - Contains flexible project setting options, such as customizing the save path for StaticMesh.

- **EditorOperatorListener Branch**:
  - Focuses on demonstrating how to optimize editor operations and enhance code efficiency.
  - Provides rich examples, showing how to bind delegates, capture, and respond to various operations within the editor, including selecting Actors under the viewport, monitoring changes in selected Actors, and managing assets in the Content Browser.
  - Allows developers to gain a deeper understanding of the editor's internal mechanisms.

- **BluePrintEditorExtension Branch**:
  - This branch is dedicated to demonstrating how to extend the Unreal Engine editor's functionality by creating blueprints.
  - Users will learn how to create an `EditorUtilityWidget`, a UI script that runs directly within the editor, enhancing its interactivity and flexibility.
  - Includes extensions for the `Content Browser` menu, allowing users to see new options when right-clicking on an Asset.
  - Demonstrates how to extend the right-click menu in the `World Outliner` for individual or specific types of Actors, thus providing additional operations and tools.
  - By extending the right-click menus of the Content Browser and World Outliner, this branch offers users more customizable operational options, making resource management and scene editing more efficient and intuitive.

## Usage Instructions

Each branch is specifically developed and optimized for particular functionalities or purposes. Users can choose and contribute to the appropriate branch based on their needs.

## Contribution Guidelines

- Contributions enhancing or optimizing the functionalities of various branches are welcome. Please submit your improvements in the respective branch or propose suggestions and needs in the issues section.
- Contributions can also be made directly via GitHub by creating a Pull Request. Ensure that your code is clear, commented, and tested before submission.
- Feel free to contact me via WeChat (ID: 596770421) to join the project discussion and contribution.

## License

This project is licensed under the MIT License. For more information, please see the [LICENSE](LICENSE) file.



## 简介

本项目是一个编辑器扩展工具集，旨在对虚幻引擎进行扩展以满足更加个性化的编辑器使用需求以及更深入了解虚幻引擎编辑器源码。本项目有多个分支，每个分支都包含不同的编辑器扩展功能，你可以根据自己的需求选择合适的分支。

## 功能特点

- **Master分支**：

    - 作为项目的核心，汇总并整合所有分支的功能。
    - 提供完整的ReadMe文件，使新用户能快速上手。
    - 未来将包括针对特定虚幻引擎版本的功能整合，便于开发者选择适合的工具集。

- **CustomAssets分支**：

    - 提供先进的自定义FBX资产导入工具，能够将FBX文件自动转换为CustomMesh UAsset。
    - 包括一个创新的菜单页扩展功能，使用户能够轻松创建CustomMesh资产。
    - 引入自定义视口和缩略图渲染功能，优化资产可视化。
    - 包含灵活的项目设置选项，例如可自定义StaticMesh的保存路径。

- **EditorOperatorListener分支**：

    - 专注于展示如何优化编辑器操作和提高代码效率。
    - 提供丰富的示例，展示如何绑定代理，捕获并响应编辑器内各种操作，包括选中视口下的Actor，监测选中Actor的变化，以及操作Content中的资产等。
    - 能够让开发者更深入了解编辑器的内部工作机制。

- ### EditorOperatorListener分支

    - 本分支专注于演示如何在虚幻引擎编辑器中通过创建蓝图扩展编辑器的功能。
    - 用户将学习如何创建一个 `EditorUtilityWidget`，这是一个在编辑器中直接运行的UI脚本，增强了编辑器的交互性和灵活性。
    - 包含对内容浏览器（`Content Browser`）的菜单栏的扩展，允许用户在右键点击资产（`Asset`）时看到新增的选项。
    - 展示了如何扩展世界大纲（`World Outliner`）中对单个或特定类型的Actor的右键菜单，从而提供额外的操作和工具。
    - 通过扩展内容浏览器和世界大纲的右键菜单，本分支为用户提供了更多定制化的操作选项，使得资源管理和场景编辑更为高效和直观。

## 使用说明
每个分支都针对特定的功能或用途进行了专门的开发和优化。用户可以根据自己的需求，选择合适的分支进行使用和贡献。

## 贡献指南
欢迎对各分支进行功能增强或优化的贡献。请在相应分支下提交您的改进方案，或在issues区提出建议和需求。


## 如何使用
1. 参考：[Installing Unreal Engine | Unreal Engine Documentation](https://docs.unrealengine.com/4.26/en-US/Basics/InstallingUnrealEngine/)
1. 引擎版本：5.3.2

## 贡献指南
- 欢迎对各分支进行功能增强或优化的贡献。请在相应分支下提交您的改进方案，或在issues区提出建议和需求。
- 也可以通过GitHub直接发起Pull Request来提交您的贡献。请确保您的代码清晰、有注释，并且在提交前进行了测试。
- 欢迎通过微信（ID: 596770421）联系我，加入项目的讨论和贡献。

## 许可证
本项目在MIT许可证下授权。有关更多信息，请参见 [LICENSE](LICENSE) 文件。
