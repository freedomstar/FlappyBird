<GameFile>
  <PropertyGroup Name="Node" Type="Node" ID="0f996a19-2b66-4c94-b984-91a798165d40" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000">
        <Timeline ActionTag="-314565505" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="birds_01.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="Normal" Path="birds_02.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="20" Tween="False">
            <TextureFile Type="Normal" Path="birds_03.png" Plist="" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="fly" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="240" G="255" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="16" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_1" ActionTag="-314565505" Tag="31" IconVisible="False" LeftMargin="-28.5983" RightMargin="-23.4017" TopMargin="-23.1498" BottomMargin="-21.8502" ctype="SpriteObjectData">
            <Size X="52.0000" Y="45.0000" />
            <AnchorPoint ScaleX="0.4500" ScaleY="0.5144" />
            <Position X="-5.1977" Y="1.2994" />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="birds_01.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>