<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.2">
  <compound kind="file">
    <name>api.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/API/include/api/</path>
    <filename>api_8hpp.html</filename>
    <includes id="_a_p_i_2include_2api_2macros_8hpp" name="API/include/api/macros.hpp" local="yes" imported="no">macros.hpp</includes>
    <class kind="class">api::ApiInfo</class>
    <class kind="class">api::Api</class>
    <class kind="class">api::Error</class>
    <class kind="class">api::Error::Backtrace</class>
    <class kind="class">api::PrivateExecutionContext</class>
    <class kind="class">api::ExecutionContext</class>
    <class kind="class">api::ErrorGuard</class>
    <class kind="class">api::ThreadExecutionContext</class>
    <class kind="class">api::Demangler</class>
    <class kind="class">api::ProgressCallback</class>
    <class kind="class">api::RangeIterator</class>
    <class kind="class">api::Range</class>
    <class kind="class">api::IndexIterator</class>
    <class kind="class">api::Index</class>
    <namespace>api</namespace>
    <member kind="define">
      <type>#define</type>
      <name>API_BACKTRACE_SIZE</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>abdce257938d1c5504113dbb2d249fbbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_THREAD_EXECUTION_CONTEXT</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a203acc8ee2df8cf9659f0855677518cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ASSERT</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a29d4ac9cd1a3d6aca1317bcfa40ec2ac</anchor>
      <arglist>(a)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RETURN_VALUE_IF_ERROR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a6f7cf9ddeaf2da18604fa2335fe237bf</anchor>
      <arglist>(return_value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RETURN_IF_ERROR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>ac913a1b48bd19630056ad292f99cfbb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_SYSTEM_CALL</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>ab9cbaadad7bc5b27e6656c3941d3c9db</anchor>
      <arglist>(message_value, return_value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_SYSTEM_CALL_NULL</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a894891431b442a6cf02d73d6f12217d4</anchor>
      <arglist>(message_value, return_value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RESET_ERROR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>aa928e815d7a29a3055f5e50ff8f8f7cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RETURN_VALUE_ASSIGN_ERROR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>ab9f18753677febf97a356d157660daba</anchor>
      <arglist>( return_value, message_value, error_number_value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RETURN_ASSIGN_ERROR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>ac6a819e9f76b3709e473f9aca91e1d43</anchor>
      <arglist>(message_value, error_number_value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_SINGLETON</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a8fd15e9f69570e493904d712f4b8bd00</anchor>
      <arglist>(class_name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_SINGLETON_CUSTOM_CONSTRUCTOR</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a2d9a67ff59efc02e6764824df54c5e5c</anchor>
      <arglist>(class_name)</arglist>
    </member>
    <member kind="typedef">
      <type>ErrorGuard</type>
      <name>ErrorContext</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>a50bccdd6a269a17ad69000a3acabfa04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ErrorGuard</type>
      <name>ErrorScope</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>a4efe504e63365f31261ab7c97d2047e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sos_trace_stack</name>
      <anchorfile>api_8hpp.html</anchorfile>
      <anchor>a0e9c97ead9503b5599f74ed0eb6d70f1</anchor>
      <arglist>(u32 count)</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>kernel_request_api</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>afafed9fab17d151041a76c41cec415fb</anchor>
      <arglist>(u32 request)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>api_assert</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>abdebff78cb996a8397e5241439324f83</anchor>
      <arglist>(bool value, const char *function, int line)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>chrono.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ChronoAPI/include/</path>
    <filename>chrono_8hpp.html</filename>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <includes id="_clock_timer_8hpp" name="ClockTimer.hpp" local="yes" imported="no">chrono/ClockTimer.hpp</includes>
    <includes id="_date_time_8hpp" name="DateTime.hpp" local="yes" imported="no">chrono/DateTime.hpp</includes>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">chrono/MicroTime.hpp</includes>
    <namespace>chrono</namespace>
  </compound>
  <compound kind="file">
    <name>ClockTime.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ChronoAPI/include/chrono/</path>
    <filename>_clock_time_8hpp.html</filename>
    <includes id="_date_time_8hpp" name="DateTime.hpp" local="yes" imported="no">DateTime.hpp</includes>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">var/StackString.hpp</includes>
    <class kind="class">chrono::ClockTime</class>
    <namespace>chrono</namespace>
    <namespace>printer</namespace>
    <member kind="function">
      <type>printer::Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a2532462d2ecf8d1bdb202902edef15fc</anchor>
      <arglist>(printer::Printer &amp;printer, const chrono::ClockTime &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ClockTimer.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ChronoAPI/include/chrono/</path>
    <filename>_clock_timer_8hpp.html</filename>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">ClockTime.hpp</includes>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">MicroTime.hpp</includes>
    <class kind="class">chrono::ClockTimer</class>
    <class kind="class">chrono::PerformanceScope</class>
    <namespace>printer</namespace>
    <namespace>chrono</namespace>
    <member kind="typedef">
      <type>PerformanceScope</type>
      <name>PerformanceContext</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>aa19019b31230c5f70b1d59edf342b762</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a47ce77951f9fff5e63d761fed3eeb4d8</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>aae876c39b8ee9c3b991b140b715c7a06</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a97fa542653ca96e6435d08ea58e08075</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>abbb697846f030df0ff4b1dfc2f2a787e</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a7a6da1efdfb4c4306c46e0275d6a572f</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a9053dd7d642e4c2353e110d24dd2a80c</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a638ad5c45140bb7dd8cdf0e6f8dbe167</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a7675e764345b0bd9e2b7751569bc7067</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a99ccee7dc7fe7a64e57d6a36173f1ae8</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a597f19e7274671f78b6921e35388b87b</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a79bc778aba26f8bf0e7865a26a700366</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a9436b14ef69a0c04b2462988d8389ff2</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>DateTime.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ChronoAPI/include/chrono/</path>
    <filename>_date_time_8hpp.html</filename>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">MicroTime.hpp</includes>
    <class kind="class">chrono::DateTime</class>
    <class kind="class">chrono::DateTime::Construct</class>
    <class kind="class">chrono::Date</class>
    <class kind="class">chrono::Date::Construct</class>
    <namespace>chrono</namespace>
    <namespace>printer</namespace>
    <member kind="function">
      <type>chrono::DateTime</type>
      <name>operator&quot;&quot;_weeks</name>
      <anchorfile>_date_time_8hpp.html</anchorfile>
      <anchor>a80d8e22c1b25a2f463dc5dc79c36ee3a</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::DateTime</type>
      <name>operator&quot;&quot;_days</name>
      <anchorfile>_date_time_8hpp.html</anchorfile>
      <anchor>a885d19f0150ab877c08f17559fbdbc30</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::DateTime</type>
      <name>operator&quot;&quot;_hours</name>
      <anchorfile>_date_time_8hpp.html</anchorfile>
      <anchor>a1345e7911f152e7af7f315acbbd01d8f</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::DateTime</type>
      <name>operator&quot;&quot;_minutes</name>
      <anchorfile>_date_time_8hpp.html</anchorfile>
      <anchor>adfb3ccf0571e21b1245008175c7ffb63</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a0026cc5e0ad54f38e57da9219a18ed93</anchor>
      <arglist>(Printer &amp;printer, const chrono::DateTime &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>MicroTime.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ChronoAPI/include/chrono/</path>
    <filename>_micro_time_8hpp.html</filename>
    <includes id="_a_p_i_2include_2api_2macros_8hpp" name="API/include/api/macros.hpp" local="yes" imported="no">api/macros.hpp</includes>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">chrono/MicroTime.hpp</includes>
    <class kind="class">chrono::MicroTime</class>
    <namespace>chrono</namespace>
    <namespace>printer</namespace>
    <member kind="typedef">
      <type>u32</type>
      <name>micro_time_t</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>af2672f65e28905521c580f1afd434ccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MicroTime</type>
      <name>Microseconds</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>ad9ceb98c3a90f286f34d6b3ccdae19ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wait</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a62492efc5b45b282bd59f32199474c42</anchor>
      <arglist>(const MicroTime &amp;duration)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator*</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>af9713261d7d761bcffa80de8814c4f33</anchor>
      <arglist>(u32 lhs, MicroTime rhs)</arglist>
    </member>
    <member kind="function">
      <type>chrono::MicroTime</type>
      <name>operator&quot;&quot;_seconds</name>
      <anchorfile>_micro_time_8hpp.html</anchorfile>
      <anchor>a27b154d2bc7006d2e079577f0532970e</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::MicroTime</type>
      <name>operator&quot;&quot;_milliseconds</name>
      <anchorfile>_micro_time_8hpp.html</anchorfile>
      <anchor>afa8c8c1249f5f5531a75c72518c42985</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::MicroTime</type>
      <name>operator&quot;&quot;_microseconds</name>
      <anchorfile>_micro_time_8hpp.html</anchorfile>
      <anchor>acbf8c287fc7e6a6b97d4634d047ed78d</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>chrono::MicroTime</type>
      <name>operator&quot;&quot;_nanoseconds</name>
      <anchorfile>_micro_time_8hpp.html</anchorfile>
      <anchor>a64922cccdbb0a62013300968a7c9897b</anchor>
      <arglist>(unsigned long long int value)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a5582f4fb098214f864c07489e1680ee7</anchor>
      <arglist>(Printer &amp;printer, const chrono::MicroTime &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>fs.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/</path>
    <filename>fs_8hpp.html</filename>
    <includes id="_aio_8hpp" name="Aio.hpp" local="yes" imported="no">fs/Aio.hpp</includes>
    <includes id="_data_file_8hpp" name="DataFile.hpp" local="yes" imported="no">fs/DataFile.hpp</includes>
    <includes id="_dir_8hpp" name="Dir.hpp" local="yes" imported="no">fs/Dir.hpp</includes>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">fs/File.hpp</includes>
    <includes id="_file_info_8hpp" name="FileInfo.hpp" local="yes" imported="no">fs/FileInfo.hpp</includes>
    <includes id="_file_system_8hpp" name="FileSystem.hpp" local="yes" imported="no">fs/FileSystem.hpp</includes>
    <includes id="_lambda_file_8hpp" name="LambdaFile.hpp" local="yes" imported="no">fs/LambdaFile.hpp</includes>
    <includes id="_path_8hpp" name="Path.hpp" local="yes" imported="no">fs/Path.hpp</includes>
    <includes id="_view_file_8hpp" name="ViewFile.hpp" local="yes" imported="no">fs/ViewFile.hpp</includes>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>Aio.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_aio_8hpp.html</filename>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">chrono/MicroTime.hpp</includes>
    <includes id="_view_8hpp" name="View.hpp" local="yes" imported="no">var/View.hpp</includes>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">File.hpp</includes>
    <class kind="class">fs::Aio</class>
    <namespace>hal</namespace>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>DataFile.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_data_file_8hpp.html</filename>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">File.hpp</includes>
    <includes id="_data_8hpp" name="Data.hpp" local="yes" imported="no">var/Data.hpp</includes>
    <class kind="class">fs::DataFile</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>Dir.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_dir_8hpp.html</filename>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">var/StackString.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">var/Vector.hpp</includes>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">File.hpp</includes>
    <includes id="_file_info_8hpp" name="FileInfo.hpp" local="yes" imported="no">FileInfo.hpp</includes>
    <class kind="class">fs::DirObject</class>
    <class kind="class">fs::DirAccess</class>
    <class kind="class">fs::Dir</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>File.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_file_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <includes id="_file_info_8hpp" name="FileInfo.hpp" local="yes" imported="no">FileInfo.hpp</includes>
    <includes id="_micro_time_8hpp" name="MicroTime.hpp" local="yes" imported="no">chrono/MicroTime.hpp</includes>
    <includes id="_base64_8hpp" name="Base64.hpp" local="yes" imported="no">var/Base64.hpp</includes>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <class kind="class">fs::FileObject</class>
    <class kind="class">fs::FileObject::Write</class>
    <class kind="class">fs::FileObject::Verify</class>
    <class kind="class">fs::FileObject::LocationGuard</class>
    <class kind="class">fs::FileObject::Ioctl</class>
    <class kind="class">fs::FileAccess</class>
    <class kind="class">fs::FileMemberAccess</class>
    <class kind="class">fs::File</class>
    <class kind="class">fs::File::DescriptorScope</class>
    <class kind="class">fs::NullFile</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>FileInfo.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_file_info_8hpp.html</filename>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <includes id="_fs_a_p_i_2include_2fs_2macros_8hpp" name="FsAPI/include/fs/macros.hpp" local="yes" imported="no">macros.hpp</includes>
    <class kind="class">fs::FileInfoFlags</class>
    <class kind="class">fs::Permissions</class>
    <class kind="class">fs::OpenMode</class>
    <class kind="class">fs::Access</class>
    <class kind="class">fs::FileInfo</class>
    <namespace>fs</namespace>
    <namespace>printer</namespace>
    <member kind="define">
      <type>#define</type>
      <name>O_BINARY</name>
      <anchorfile>_file_info_8hpp.html</anchorfile>
      <anchor>a36fa9b2e726512bc17a7a6d3e39002be</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a0ccb430b295e63492dbe238eeac1142b</anchor>
      <arglist>(Printer &amp;printer, const fs::FileInfo &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>FileSystem.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_file_system_8hpp.html</filename>
    <includes id="_dir_8hpp" name="Dir.hpp" local="yes" imported="no">Dir.hpp</includes>
    <class kind="class">fs::FileSystem</class>
    <class kind="class">fs::FileSystem::Rename</class>
    <namespace>fs</namespace>
    <namespace>printer</namespace>
    <member kind="typedef">
      <type>var::Vector&lt; var::PathString &gt;</type>
      <name>PathList</name>
      <anchorfile>namespacefs.html</anchorfile>
      <anchor>a268f5f3572ece215c66853b85c003c33</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a3cc387ebf4e0d90ce8647c10a1d67f69</anchor>
      <arglist>(Printer &amp;printer, const fs::PathList &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>LambdaFile.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_lambda_file_8hpp.html</filename>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">File.hpp</includes>
    <class kind="class">fs::LambdaFile</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>API/include/api/macros.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/API/include/api/</path>
    <filename>_a_p_i_2include_2api_2macros_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>API_DEPRECATED</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a6fa66e39f7aa48338a1021993e71b9fb</anchor>
      <arglist>(message)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_DEPRECATED_NO_REPLACEMENT</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>af5277eb3b1d87eb771d75a3924f50891</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_MAYBE_UNUSED</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>af36aa7a213e809cb1ab04922f771fcce</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_NO_DISCARD</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>af9355daa60aa55cef8702d11c7d01a6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_NO_RETURN</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ae41befd622ab74ddbc14cbe30a54bed7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_FALLTHROUGH</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a73fb7277757a76997be1991b8b0d5adf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_BOOL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a7325820aacdd2d053fefdc8024d9a582</anchor>
      <arglist>(c, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AB</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ae5f0206da72cce272e93aa4640d3177c</anchor>
      <arglist>(c, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_READ_ACCESS_BOOL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a630a7fc6e980215f58b77fc0877dfe93</anchor>
      <arglist>(c, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RAB</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a891584cfbe843488a43089a0237c8371</anchor>
      <arglist>(c, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_FUNDAMENTAL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ad3f264c42ea9e4185723811b54526a33</anchor>
      <arglist>(c, t, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a5c6d93c2448ea376cbdd80c96e691602</anchor>
      <arglist>(c, t, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_PUBLIC_MEMBER</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aa5b3efa4dbd53ec143c4c26c8cf1b112</anchor>
      <arglist>(CLASS, TYPE, NAME, INITIAL_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_PUBLIC_MEMBER_AZ</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a34c47f388597e20d62f2a5587d2c3e51</anchor>
      <arglist>(NAME, CLASS, TYPE, INITIAL_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_PMAZ</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a77fc95cd850b39ddba523873dd49eeb9</anchor>
      <arglist>(NAME, CLASS, TYPE, INITIAL_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_PUBLIC_BOOL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a9b7a52df45df1aeec633659f9c87f7d7</anchor>
      <arglist>(CLASS, NAME, INITIAL_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_MEMBER_FUNDAMENTAL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ade3d832ae563aaed992b9dbbeeabc8d5</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AMF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a67618e7b27eaab18ecf6fbb47f1749a9</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_READ_ACCESS_MEMBER_FUNDAMENTAL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aade7cbdcb6196002b1ab5a90833ac6b1</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RAMF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a9749f6594a10145ae9c6a835e71a9f4a</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_MEMBER_FUNDAMENTAL_WITH_ALIAS</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a839f2470047e3048a65efbd52779b065</anchor>
      <arglist>(c, t, p, a, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AMFWA</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a816437dc3e2a910cc5c2026fe9ed8e1b</anchor>
      <arglist>(c, t, p, a, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_MEMBER_COMPOUND</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aeba5e23d057360967a9a7d257a4e3f5b</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AMC</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a3d375df985a29708d7c42f54d2484c71</anchor>
      <arglist>(c, t, p, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_READ_ACCESS_FUNDAMENTAL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a770cbb0907ad89dcff03b2d0c070c2dd</anchor>
      <arglist>(c, t, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RAF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a4582155e3567df017e67badeb601170b</anchor>
      <arglist>(c, t, v, iv)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_COMPOUND</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ad8f45e953813168502b861881591747c</anchor>
      <arglist>(c, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AC</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a3485ff5d757e181b9abcbbd7a8bc8746</anchor>
      <arglist>(c, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_STRING</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aca24e51775ed7ae800622eecf6b09f1b</anchor>
      <arglist>(PARENT_VALUE, VALUE_NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_AS</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>afdc8f198584ad47f4ec675001581ac0b</anchor>
      <arglist>(PARENT_VALUE, VALUE_NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_READ_ACCESS_COMPOUND</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ad69b79c32e2015bdd85001403363795b</anchor>
      <arglist>(c, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_RAC</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a8c46a61275a7f72a55ecb531c37e2ce8</anchor>
      <arglist>(c, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_DERIVED_COMPOUND</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a4e3c4f8ec2f9f8bc60b6ec30eeb4e3cb</anchor>
      <arglist>(c, d, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ADC</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>af52ef670405849a7b2034dfde15194da</anchor>
      <arglist>(c, d, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_DERIVED_FUNDAMETAL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a036eb152b05062faa4085df6a45fa29b</anchor>
      <arglist>(c, d, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ADF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a48e7711545b6923a333a870152a0b81c</anchor>
      <arglist>(c, d, t, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ACCESS_DERIVED_BOOL</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ab80b422c64dccfa25fc33e66b8d02a46</anchor>
      <arglist>(c, d, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ADB</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a01116f206bb722b28068e550fa2179de</anchor>
      <arglist>(c, d, v)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_OR_ENUM_CLASS</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aa94440e856e44d5c0514458bdd95b575</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_OR_NAMED_FLAGS_OPERATOR</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ab09a72dea2f90468d84bf15684d4747c</anchor>
      <arglist>(TYPE, FLAG_NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_OR_FLAGS_OPERATOR</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a0d90e92a0ec2af1045972e73769fee5f</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_ENUM_LOOP_OPERATOR</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a8dc7bdf68df14925a472a997c687476b</anchor>
      <arglist>(TYPE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_MALLOC_CHUNK_SIZE</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ac37e1d0b6212812dc3ce51252222e17d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_MINIMUM_CHUNK_SIZE</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a0f3171246f37d9e66049463bdf08ffe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_CONST_CAST_SELF</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ae677523485836adc4351c0350d620ba2</anchor>
      <arglist>(type_value, function_value,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_CONST_CAST</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>aec7fc12a6a15eac60f531720baaa2bb9</anchor>
      <arglist>(type_value, function_value,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_WRITE_ACCESS_COMPOUND_ALIAS</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>ab27296987d67e1c7ad43e1d548770456</anchor>
      <arglist>(PARENT, DERIVED, TYPE, NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_WRITE_ACCESS_FUNDAMENTAL_ALIAS</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a0afa0ac0edb642a76342f37409d01d93</anchor>
      <arglist>(PARENT, DERIVED, TYPE, NAME)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>API_PRINTF_TRACE_LINE</name>
      <anchorfile>_a_p_i_2include_2api_2macros_8hpp.html</anchorfile>
      <anchor>a59db52fbbd361aa5024e238b97f5681e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>FsAPI/include/fs/macros.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_fs_a_p_i_2include_2fs_2macros_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>MCU_INT_CAST</name>
      <anchorfile>_fs_a_p_i_2include_2fs_2macros_8hpp.html</anchorfile>
      <anchor>aa51eeac3f9dbe5557634373418f54958</anchor>
      <arglist>(var)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FSAPI_LINK_DEFAULT_PAGE_SIZE</name>
      <anchorfile>_fs_a_p_i_2include_2fs_2macros_8hpp.html</anchorfile>
      <anchor>ac5ac9f43e9b738312b6c52f643f10936</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Path.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_path_8hpp.html</filename>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="class">fs::Path</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>ViewFile.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/FsAPI/include/fs/</path>
    <filename>_view_file_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">File.hpp</includes>
    <class kind="class">fs::ViewFile</class>
    <namespace>fs</namespace>
  </compound>
  <compound kind="file">
    <name>JsonPrinter.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/PrinterAPI/include/printer/</path>
    <filename>_json_printer_8hpp.html</filename>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">var/Vector.hpp</includes>
    <includes id="printer_2_printer_8hpp" name="printer/Printer.hpp" local="yes" imported="no">Printer.hpp</includes>
    <class kind="class">printer::JsonPrinter</class>
    <namespace>printer</namespace>
  </compound>
  <compound kind="file">
    <name>MarkdownPrinter.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/PrinterAPI/include/printer/</path>
    <filename>_markdown_printer_8hpp.html</filename>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">var/Vector.hpp</includes>
    <includes id="printer_2_printer_8hpp" name="printer/Printer.hpp" local="yes" imported="no">Printer.hpp</includes>
    <class kind="class">printer::MarkdownPrinter</class>
    <class kind="class">printer::MarkdownPrinter::Header</class>
    <class kind="class">printer::MarkdownPrinter::Code</class>
    <class kind="class">printer::MarkdownPrinter::BlockQuote</class>
    <class kind="class">printer::MarkdownPrinter::Paragraph</class>
    <class kind="class">printer::MarkdownPrinter::List</class>
    <class kind="class">printer::MarkdownPrinter::PrettyTable</class>
    <namespace>printer</namespace>
  </compound>
  <compound kind="file">
    <name>Printer.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/PrinterAPI/include/</path>
    <filename>_printer_8hpp.html</filename>
    <includes id="printer_2_printer_8hpp" name="printer/Printer.hpp" local="yes" imported="no">printer/Printer.hpp</includes>
    <includes id="_json_printer_8hpp" name="JsonPrinter.hpp" local="yes" imported="no">printer/JsonPrinter.hpp</includes>
    <includes id="_markdown_printer_8hpp" name="MarkdownPrinter.hpp" local="yes" imported="no">printer/MarkdownPrinter.hpp</includes>
    <includes id="_yaml_printer_8hpp" name="YamlPrinter.hpp" local="yes" imported="no">printer/YamlPrinter.hpp</includes>
    <namespace>printer</namespace>
  </compound>
  <compound kind="file">
    <name>printer/Printer.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/PrinterAPI/include/printer/</path>
    <filename>printer_2_printer_8hpp.html</filename>
    <includes id="_data_8hpp" name="Data.hpp" local="yes" imported="no">var/Data.hpp</includes>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <includes id="_view_8hpp" name="View.hpp" local="yes" imported="no">var/View.hpp</includes>
    <class kind="struct">printer::PrinterFlags</class>
    <class kind="class">printer::PrinterTermination</class>
    <class kind="class">printer::Printer</class>
    <class kind="class">printer::Printer::FlagScope</class>
    <class kind="class">printer::Printer::LevelScope</class>
    <class kind="class">printer::Printer::Object</class>
    <class kind="class">printer::Printer::Array</class>
    <class kind="class">printer::Printer::ContainerAccess</class>
    <class kind="class">printer::NullPrinter</class>
    <namespace>api</namespace>
    <namespace>printer</namespace>
    <member kind="define">
      <type>#define</type>
      <name>PRINTER_TRACE</name>
      <anchorfile>printer_2_printer_8hpp.html</anchorfile>
      <anchor>a84075a7fdbebeb4478de147512386536</anchor>
      <arglist>(printer, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PRINTER_TRACE_ERROR</name>
      <anchorfile>printer_2_printer_8hpp.html</anchorfile>
      <anchor>ad78deadade0c13c9fdacd7d12834bf3a</anchor>
      <arglist>(printer, x)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>YamlPrinter.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/PrinterAPI/include/printer/</path>
    <filename>_yaml_printer_8hpp.html</filename>
    <includes id="printer_2_printer_8hpp" name="printer/Printer.hpp" local="yes" imported="no">Printer.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">var/Vector.hpp</includes>
    <class kind="class">printer::YamlPrinter</class>
    <namespace>printer</namespace>
  </compound>
  <compound kind="file">
    <name>sys.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/</path>
    <filename>sys_8hpp.html</filename>
    <includes id="_cli_8hpp" name="Cli.hpp" local="yes" imported="no">sys/Cli.hpp</includes>
    <includes id="_system_8hpp" name="System.hpp" local="yes" imported="no">sys/System.hpp</includes>
    <includes id="_temporary_directory_8hpp" name="TemporaryDirectory.hpp" local="yes" imported="no">sys/TemporaryDirectory.hpp</includes>
    <includes id="_version_8hpp" name="Version.hpp" local="yes" imported="no">sys/Version.hpp</includes>
    <namespace>sys</namespace>
  </compound>
  <compound kind="file">
    <name>Cli.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_cli_8hpp.html</filename>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="class">sys::Cli</class>
    <class kind="class">sys::Cli::HandleVersion</class>
    <class kind="class">sys::Cli::ShowHelp</class>
    <namespace>sys</namespace>
    <namespace>printer</namespace>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a1b63fa4718f079fac972a1dcb316a522</anchor>
      <arglist>(Printer &amp;printer, const sys::Cli &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Pipe.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_pipe_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>Process.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_process_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>System.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_system_8hpp.html</filename>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="class">sys::System</class>
    <namespace>sys</namespace>
  </compound>
  <compound kind="file">
    <name>TemporaryDirectory.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_temporary_directory_8hpp.html</filename>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">var/StackString.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="class">sys::TemporaryDirectory</class>
    <namespace>sys</namespace>
  </compound>
  <compound kind="file">
    <name>Version.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/SysAPI/include/sys/</path>
    <filename>_version_8hpp.html</filename>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">var/StackString.hpp</includes>
    <class kind="class">sys::Version</class>
    <namespace>sys</namespace>
  </compound>
  <compound kind="file">
    <name>Case.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/TestAPI/include/test/</path>
    <filename>_case_8hpp.html</filename>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <class kind="class">test::Case</class>
    <namespace>test</namespace>
  </compound>
  <compound kind="file">
    <name>Engine.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/TestAPI/include/test/</path>
    <filename>_engine_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>Function.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/TestAPI/include/test/</path>
    <filename>_function_8hpp.html</filename>
    <includes id="_case_8hpp" name="Case.hpp" local="yes" imported="no">Case.hpp</includes>
    <includes id="test_2_test_8hpp" name="test/Test.hpp" local="yes" imported="no">Test.hpp</includes>
    <class kind="class">test::Function</class>
    <namespace>test</namespace>
  </compound>
  <compound kind="file">
    <name>Test.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/TestAPI/include/</path>
    <filename>_test_8hpp.html</filename>
    <includes id="_case_8hpp" name="Case.hpp" local="yes" imported="no">test/Case.hpp</includes>
    <includes id="test_2_test_8hpp" name="test/Test.hpp" local="yes" imported="no">test/Test.hpp</includes>
    <namespace>test</namespace>
  </compound>
  <compound kind="file">
    <name>test/Test.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/TestAPI/include/test/</path>
    <filename>test_2_test_8hpp.html</filename>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <includes id="_clock_timer_8hpp" name="ClockTimer.hpp" local="yes" imported="no">chrono/ClockTimer.hpp</includes>
    <includes id="printer_2_printer_8hpp" name="printer/Printer.hpp" local="yes" imported="no">printer/Printer.hpp</includes>
    <includes id="_cli_8hpp" name="Cli.hpp" local="yes" imported="no">sys/Cli.hpp</includes>
    <includes id="_data_8hpp" name="Data.hpp" local="yes" imported="no">var/Data.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="struct">test::TestFlags</class>
    <class kind="class">test::Test</class>
    <class kind="class">test::Test::Initialize</class>
    <class kind="class">test::Test::Scope</class>
    <class kind="class">test::Test::TimedScope</class>
    <namespace>test</namespace>
    <member kind="define">
      <type>#define</type>
      <name>TEST_ASSERT_RESULT</name>
      <anchorfile>test_2_test_8hpp.html</anchorfile>
      <anchor>acce2715790bc4fe2d8d5828ed7905be0</anchor>
      <arglist>(RESULT_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TEST_EXPECT</name>
      <anchorfile>test_2_test_8hpp.html</anchorfile>
      <anchor>a0ad6f16d8bc079ff5ea96780bd4f91d2</anchor>
      <arglist>(RESULT_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TEST_ASSERT</name>
      <anchorfile>test_2_test_8hpp.html</anchorfile>
      <anchor>aade90117807ddb61a240488e74d58d34</anchor>
      <arglist>(RESULT_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TEST_SELF_EXPECT</name>
      <anchorfile>test_2_test_8hpp.html</anchorfile>
      <anchor>adfed3d5a6219628db3d087438461aba5</anchor>
      <arglist>(RESULT_VALUE)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TEST_SELF_ASSERT</name>
      <anchorfile>test_2_test_8hpp.html</anchorfile>
      <anchor>a11bf6189f325daffd3f9bb50211c7f88</anchor>
      <arglist>(RESULT_VALUE)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>thread.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/</path>
    <filename>thread_8hpp.html</filename>
    <includes id="_cond_8hpp" name="Cond.hpp" local="yes" imported="no">thread/Cond.hpp</includes>
    <includes id="_mutex_8hpp" name="Mutex.hpp" local="yes" imported="no">thread/Mutex.hpp</includes>
    <includes id="_mq_8hpp" name="Mq.hpp" local="yes" imported="no">thread/Mq.hpp</includes>
    <includes id="_sched_8hpp" name="Sched.hpp" local="yes" imported="no">thread/Sched.hpp</includes>
    <includes id="_sem_8hpp" name="Sem.hpp" local="yes" imported="no">thread/Sem.hpp</includes>
    <includes id="_signal_8hpp" name="Signal.hpp" local="yes" imported="no">thread/Signal.hpp</includes>
    <includes id="thread_2thread_8hpp" name="thread/thread.hpp" local="yes" imported="no">thread/Thread.hpp</includes>
    <includes id="_timer_8hpp" name="Timer.hpp" local="yes" imported="no">thread/Timer.hpp</includes>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>thread/thread.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>thread_2thread_8hpp.html</filename>
    <includes id="_sched_8hpp" name="Sched.hpp" local="yes" imported="no">Sched.hpp</includes>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <class kind="class">thread::Thread</class>
    <class kind="class">thread::Thread::Attributes</class>
    <class kind="class">thread::Thread::Construct</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Cond.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_cond_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="no" imported="no">api/api.hpp</includes>
    <includes id="_mutex_8hpp" name="Mutex.hpp" local="yes" imported="no">Mutex.hpp</includes>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <class kind="class">thread::Cond</class>
    <class kind="class">thread::Cond::Attributes</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Mq.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_mq_8hpp.html</filename>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <includes id="_file_8hpp" name="File.hpp" local="yes" imported="no">fs/File.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <class kind="class">thread::Mq</class>
    <class kind="class">thread::Mq::Attributes</class>
    <class kind="class">thread::Mq::Info</class>
    <class kind="class">thread::Mq::File</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Mutex.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_mutex_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <includes id="_array_8hpp" name="Array.hpp" local="yes" imported="no">var/Array.hpp</includes>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <class kind="class">thread::Mutex</class>
    <class kind="class">thread::Mutex::Attributes</class>
    <class kind="class">thread::Mutex::Guard</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Sched.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_sched_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">thread::Sched</class>
    <class kind="class">thread::Sched::SetScheduler</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Sem.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_sem_8hpp.html</filename>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <includes id="_file_info_8hpp" name="FileInfo.hpp" local="yes" imported="no">fs/FileInfo.hpp</includes>
    <includes id="_path_8hpp" name="Path.hpp" local="yes" imported="no">fs/Path.hpp</includes>
    <class kind="class">thread::SemaphoreObject</class>
    <class kind="class">thread::SemAccess</class>
    <class kind="class">thread::UnnamedSemaphore</class>
    <class kind="class">thread::Semaphore</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>Signal.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_signal_8hpp.html</filename>
    <includes id="_sched_8hpp" name="Sched.hpp" local="yes" imported="no">Sched.hpp</includes>
    <includes id="thread_2thread_8hpp" name="thread/thread.hpp" local="yes" imported="no">Thread.hpp</includes>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">thread::SignalFlags</class>
    <class kind="class">thread::SignalHandler</class>
    <class kind="class">thread::SignalHandler::Construct</class>
    <class kind="class">thread::Signal</class>
    <class kind="class">thread::Signal::Event</class>
    <class kind="class">thread::Signal::Set</class>
    <class kind="class">thread::Signal::HandlerScope</class>
    <namespace>thread</namespace>
    <member kind="define">
      <type>#define</type>
      <name>THREAD_API_POSIX_KILL</name>
      <anchorfile>_signal_8hpp.html</anchorfile>
      <anchor>a44c08a0e870d28a76b021d1df2060874</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Timer.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/ThreadAPI/include/thread/</path>
    <filename>_timer_8hpp.html</filename>
    <includes id="_signal_8hpp" name="Signal.hpp" local="yes" imported="no">Signal.hpp</includes>
    <includes id="_clock_time_8hpp" name="ClockTime.hpp" local="yes" imported="no">chrono/ClockTime.hpp</includes>
    <class kind="class">thread::Timer</class>
    <class kind="class">thread::Timer::SetTime</class>
    <class kind="class">thread::Timer::Info</class>
    <class kind="class">thread::Timer::Alarm</class>
    <namespace>thread</namespace>
  </compound>
  <compound kind="file">
    <name>var.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/</path>
    <filename>var_8hpp.html</filename>
    <includes id="_array_8hpp" name="Array.hpp" local="yes" imported="no">var/Array.hpp</includes>
    <includes id="_base64_8hpp" name="Base64.hpp" local="yes" imported="no">var/Base64.hpp</includes>
    <includes id="_data_8hpp" name="Data.hpp" local="yes" imported="no">var/Data.hpp</includes>
    <includes id="_deque_8hpp" name="Deque.hpp" local="yes" imported="no">var/Deque.hpp</includes>
    <includes id="_flags_8hpp" name="Flags.hpp" local="yes" imported="no">var/Flags.hpp</includes>
    <includes id="_queue_8hpp" name="Queue.hpp" local="yes" imported="no">var/Queue.hpp</includes>
    <includes id="_ring_8hpp" name="Ring.hpp" local="yes" imported="no">var/Ring.hpp</includes>
    <includes id="_stack_8hpp" name="Stack.hpp" local="yes" imported="no">var/Stack.hpp</includes>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">var/StackString.hpp</includes>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">var/String.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">var/StringView.hpp</includes>
    <includes id="_tokenizer_8hpp" name="Tokenizer.hpp" local="yes" imported="no">var/Tokenizer.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">var/Vector.hpp</includes>
    <includes id="_view_8hpp" name="View.hpp" local="yes" imported="no">var/View.hpp</includes>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Array.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_array_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::Array</class>
    <class kind="class">var::Pair</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Base64.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_base64_8hpp.html</filename>
    <includes id="_view_8hpp" name="View.hpp" local="yes" imported="no">var/View.hpp</includes>
    <class kind="class">var::Base64</class>
    <class kind="class">var::Base64Encoder</class>
    <class kind="class">var::Base64Decoder</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>ContainerObject.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_container_object_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::ContainerObject</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Data.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_data_8hpp.html</filename>
    <includes id="_view_8hpp" name="View.hpp" local="yes" imported="no">View.hpp</includes>
    <class kind="class">var::DataInfo</class>
    <class kind="class">var::Data</class>
    <class kind="class">var::Data::Copy</class>
    <class kind="class">var::Data::Erase</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Deque.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_deque_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::Deque</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Flags.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_flags_8hpp.html</filename>
    <class kind="class">var::Bits</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>List.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_list_8hpp.html</filename>
    <includes id="_queue_8hpp" name="Queue.hpp" local="yes" imported="no">Queue.hpp</includes>
  </compound>
  <compound kind="file">
    <name>Matrix.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_matrix_8hpp.html</filename>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">Vector.hpp</includes>
    <class kind="class">var::Matrix</class>
    <namespace>var</namespace>
    <member kind="function">
      <type>printer::Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a5b203af4c63c908ff786a8d80e6e84ab</anchor>
      <arglist>(printer::Printer &amp;printer, const Matrix&lt; T &gt; &amp;matrix)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Queue.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_queue_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::Queue</class>
    <class kind="class">var::Queue::Erase</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Ring.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_ring_8hpp.html</filename>
    <includes id="_array_8hpp" name="Array.hpp" local="yes" imported="no">Array.hpp</includes>
    <class kind="class">var::Ring</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>Stack.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_stack_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::Stack</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>StackString.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_stack_string_8hpp.html</filename>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">String.hpp</includes>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">StringView.hpp</includes>
    <class kind="class">var::StackString</class>
    <class kind="class">var::StackString::Replace</class>
    <class kind="class">var::IdString</class>
    <class kind="class">var::NameString</class>
    <class kind="class">var::KeyString</class>
    <class kind="class">var::PathString</class>
    <class kind="class">var::GeneralString</class>
    <class kind="class">var::NumberString</class>
    <namespace>var</namespace>
    <member kind="define">
      <type>#define</type>
      <name>PATH_STRING_LENGTH</name>
      <anchorfile>_stack_string_8hpp.html</anchorfile>
      <anchor>a1010415e21b0cf246bed92b45c6f958c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VAR_API_GENERAL_STRING_SIZE</name>
      <anchorfile>_stack_string_8hpp.html</anchorfile>
      <anchor>abd074bc694a2ae4801fc994440e9a9d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>NumberString</type>
      <name>StackString64</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ab8da8f9be9708e0504562baa3f7bb09d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator&amp;</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a331680fd15fb1537023be86d5828513e</anchor>
      <arglist>(const StringView lhs, const StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator/</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ac5fc826094648ab7aab81bc04e47ef2d</anchor>
      <arglist>(const StringView lhs, const StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>GeneralString</type>
      <name>operator|</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a12affee639138783e9f32808d8770750</anchor>
      <arglist>(StringView lhs, StringView rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>String.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_string_8hpp.html</filename>
    <includes id="_string_view_8hpp" name="StringView.hpp" local="yes" imported="no">StringView.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">Vector.hpp</includes>
    <class kind="class">var::String</class>
    <class kind="class">var::String::Erase</class>
    <class kind="class">var::String::Insert</class>
    <class kind="class">var::String::Compare</class>
    <class kind="class">var::String::Replace</class>
    <namespace>var</namespace>
    <member kind="typedef">
      <type>Vector&lt; String &gt;</type>
      <name>StringList</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ae6d46a5a5b3922626c34c5a470414ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>abe580a67cadc084787f83a9f43ff3481</anchor>
      <arglist>(StringView lhs, const String &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>aebbd64f7ea5551a91366045da8c81bb6</anchor>
      <arglist>(StringView lhs, StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>aeec2fc14c5a6bb40cfc239c02d524f08</anchor>
      <arglist>(const String &amp;lhs, StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a9c21e7bd6040c6f6d74c4081f3186dfe</anchor>
      <arglist>(StringView lhs, String &amp;&amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>StringUtil.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_string_util_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>StringView.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_string_view_8hpp.html</filename>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">Vector.hpp</includes>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::StringView</class>
    <class kind="class">var::StringView::GetSubstring</class>
    <namespace>var</namespace>
    <member kind="typedef">
      <type>Vector&lt; StringView &gt;</type>
      <name>StringViewList</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a6ecee59ce59f51bcc0a1189ed84d554a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>atoff</name>
      <anchorfile>_string_view_8hpp.html</anchorfile>
      <anchor>adf06c8457f0c6f52f8084e7320302909</anchor>
      <arglist>(const char *)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a92a73a6163a153697b1ae09ad7595f47</anchor>
      <arglist>(const char *lhs, StringView rhs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Tokenizer.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_tokenizer_8hpp.html</filename>
    <includes id="_data_8hpp" name="Data.hpp" local="yes" imported="no">Data.hpp</includes>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">String.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">Vector.hpp</includes>
    <class kind="class">var::Tokenizer</class>
    <class kind="class">var::Tokenizer::Construct</class>
    <namespace>var</namespace>
    <member kind="typedef">
      <type>Tokenizer</type>
      <name>Token</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a36f3577938a5e5a0d25122dcd2381ab9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Vector.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_vector_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <class kind="class">var::Vector</class>
    <class kind="class">var::Vector::Erase</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="file">
    <name>View.hpp</name>
    <path>/Users/tgil/gitv4/stratifylabs-docs/SDK/dependencies/API/libraries/VarAPI/include/var/</path>
    <filename>_view_8hpp.html</filename>
    <includes id="api_8hpp" name="api.hpp" local="yes" imported="no">api/api.hpp</includes>
    <includes id="_array_8hpp" name="Array.hpp" local="yes" imported="no">Array.hpp</includes>
    <includes id="_stack_string_8hpp" name="StackString.hpp" local="yes" imported="no">StackString.hpp</includes>
    <includes id="_string_8hpp" name="String.hpp" local="yes" imported="no">String.hpp</includes>
    <includes id="_vector_8hpp" name="Vector.hpp" local="yes" imported="no">Vector.hpp</includes>
    <class kind="class">var::View</class>
    <class kind="class">var::Transformer</class>
    <class kind="class">var::Transformer::Transform</class>
    <namespace>var</namespace>
  </compound>
  <compound kind="class">
    <name>api::Api</name>
    <filename>classapi_1_1_api.html</filename>
    <templarg>typename A</templarg>
    <templarg>u32 request</templarg>
    <member kind="function">
      <type></type>
      <name>Api</name>
      <anchorfile>classapi_1_1_api.html</anchorfile>
      <anchor>a0f8a74bcda96817d1ebe039593ee3000</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classapi_1_1_api.html</anchorfile>
      <anchor>a1344e467e7bb70c12266148c8b91c419</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Api &amp;</type>
      <name>operator=</name>
      <anchorfile>classapi_1_1_api.html</anchorfile>
      <anchor>ac43eca20a4faf92e340e0adb3cad3927</anchor>
      <arglist>(const A *value)</arglist>
    </member>
    <member kind="function">
      <type>const A *</type>
      <name>operator-&gt;</name>
      <anchorfile>classapi_1_1_api.html</anchorfile>
      <anchor>a1fbd175e9a9c973f3eb68394dcb43af2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const A *</type>
      <name>api</name>
      <anchorfile>classapi_1_1_api.html</anchorfile>
      <anchor>ac098e8da3b6d6430989cc2ad89fad05f</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::ApiInfo</name>
    <filename>classapi_1_1_api_info.html</filename>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>version</name>
      <anchorfile>classapi_1_1_api_info.html</anchorfile>
      <anchor>a96d7467584ec444eaddecf2e75ca7e5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>git_hash</name>
      <anchorfile>classapi_1_1_api_info.html</anchorfile>
      <anchor>a343660af8440acde30eee2ef90c0e1f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr u32</type>
      <name>malloc_start_chunk_size</name>
      <anchorfile>classapi_1_1_api_info.html</anchorfile>
      <anchor>aadb6c345f04f937525b5169c196c3ddb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr u32</type>
      <name>malloc_chunk_size</name>
      <anchorfile>classapi_1_1_api_info.html</anchorfile>
      <anchor>a211e2b1a63eb5b64ee07a1346c46abee</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::Demangler</name>
    <filename>classapi_1_1_demangler.html</filename>
    <member kind="function">
      <type></type>
      <name>Demangler</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>a763e23350735f84e18cab07a242d7c1a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Demangler</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>a1a427889961aff021de11783822c7a47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Demangler</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>a56e1db3a66198212f1495e288aa92ac2</anchor>
      <arglist>(const Demangler &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>Demangler &amp;</type>
      <name>operator=</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>ad98b35d1614b7c2ff4b7819affcdf55b</anchor>
      <arglist>(const Demangler &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Demangler</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>ad73dd99840a0e0b00406ab9d8d3bd0be</anchor>
      <arglist>(Demangler &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>Demangler &amp;</type>
      <name>operator=</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>ae5a58ca317f36879497220606ad39a1a</anchor>
      <arglist>(Demangler &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>demangle</name>
      <anchorfile>classapi_1_1_demangler.html</anchorfile>
      <anchor>a50889aacaa4f50d8371839f5ef9281cf</anchor>
      <arglist>(const char *input)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::Error</name>
    <filename>classapi_1_1_error.html</filename>
    <class kind="class">api::Error::Backtrace</class>
    <member kind="function">
      <type>const char *</type>
      <name>message</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>a86239ce091dc71856bd665831c27ed4d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>error_number</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>ab74a4a74cd8f8631ffa8df80939d2cee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>line_number</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>aa07da2637d5fb8ecd8be5aca321397e6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>signature</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>a188fab6c3303230ae9353bacf59cc8e7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_error</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>a0ae0464e1d576efe976baec80a3cfb42</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>af4412577dd84fa9899e1586032f29495</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_guarded</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>ab665c0a08b27561586909d67621d6ab5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_guarded</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>a2a0fc1485bd6f561c8fb89d9b5770531</anchor>
      <arglist>(bool value=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>constexpr static size_t</type>
      <name>backtrace_buffer_size</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>ad8bce7cc0ece17ec882291e3b123845a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>PrivateExecutionContext</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>ad2850542435e657b278ceb4ba5c3af6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>BacktraceSymbols</name>
      <anchorfile>classapi_1_1_error.html</anchorfile>
      <anchor>a1d913e17536c16ea3dcb2e4898b6c392</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::Error::Backtrace</name>
    <filename>classapi_1_1_error_1_1_backtrace.html</filename>
    <member kind="function">
      <type></type>
      <name>Backtrace</name>
      <anchorfile>classapi_1_1_error_1_1_backtrace.html</anchorfile>
      <anchor>a343b55154ae3d9acca6e700ce801e039</anchor>
      <arglist>(const Error &amp;context)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>at</name>
      <anchorfile>classapi_1_1_error_1_1_backtrace.html</anchorfile>
      <anchor>a3dcc82f43b100db303780cd098d11375</anchor>
      <arglist>(size_t offset)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Backtrace</name>
      <anchorfile>classapi_1_1_error_1_1_backtrace.html</anchorfile>
      <anchor>a9d7e8e07335f71fb3c2179e825939b36</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::ErrorGuard</name>
    <filename>classapi_1_1_error_guard.html</filename>
    <member kind="function">
      <type></type>
      <name>ErrorGuard</name>
      <anchorfile>classapi_1_1_error_guard.html</anchorfile>
      <anchor>a3766f85e831ccded05ab39d2f15be3f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ErrorGuard</name>
      <anchorfile>classapi_1_1_error_guard.html</anchorfile>
      <anchor>aaf97413c80621817ac344154bb6ee5e8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::ExecutionContext</name>
    <filename>classapi_1_1_execution_context.html</filename>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>handle_system_call_result</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>abe0670b0e9cdc51ed9e4a8f149befa37</anchor>
      <arglist>(int line, const char *message, int value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>handle_system_call_null_result</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>abe4eedd752a09e448e4ddfc38915c2d8</anchor>
      <arglist>(int line, const char *message, T *value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Error &amp;</type>
      <name>error</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>a856b03dd0b7c7732647427e22226898c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>free_context</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>ab048cd82d85bb12f5866722012f09bcc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>exit_fatal</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>a4ec3d1f36462eb85a35a835dd2df9fac</anchor>
      <arglist>(const char *message)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static size_t</type>
      <name>context_count</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>a79ba50868f43a40ce4f5406a56fd0845</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>reset_error</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>ab28ff28529a36ab1281f4a76dac43e67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_error</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>ac0e1592ccf0272449e692ead348fadf6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_success</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>a853635c194f91fc61577f670db986be0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>return_value</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>ad9199bc3e70a5685dac83e068ec0303a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>ErrorGuard</name>
      <anchorfile>classapi_1_1_execution_context.html</anchorfile>
      <anchor>aece684bf8d8d23557e2da48457abbf93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::Index</name>
    <filename>classapi_1_1_index.html</filename>
    <templarg>typename Type</templarg>
    <member kind="function">
      <type>constexpr</type>
      <name>Index</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>a60ccbd7d5af08bb76b4bc4d2d0708220</anchor>
      <arglist>(const Type &amp;start, const Type &amp;finish)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>Index</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>acd4efc1736ea894af11796b6e841439c</anchor>
      <arglist>(const Type &amp;finish)</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator&lt; Type &gt;</type>
      <name>begin</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>a54ab3c0a20737eba0f46339f2d78c8a9</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator&lt; Type &gt;</type>
      <name>end</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>a230f9ab143ed9719aa5d2ab7e081ab4c</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator&lt; Type &gt;</type>
      <name>cbegin</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>ad8722ef7f2fb1dcb1d2fd77a6d0a51d1</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator&lt; Type &gt;</type>
      <name>cend</name>
      <anchorfile>classapi_1_1_index.html</anchorfile>
      <anchor>a8b1490264db61cd501e50a2287e65fdd</anchor>
      <arglist>() const noexcept</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::IndexIterator</name>
    <filename>classapi_1_1_index_iterator.html</filename>
    <templarg>typename Type</templarg>
    <member kind="function">
      <type></type>
      <name>IndexIterator</name>
      <anchorfile>classapi_1_1_index_iterator.html</anchorfile>
      <anchor>a7aeab49e12000da6da3a7aa3bba9e0a7</anchor>
      <arglist>(Type value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classapi_1_1_index_iterator.html</anchorfile>
      <anchor>aeedb4d2580434ef773fb3d51382aeba4</anchor>
      <arglist>(IndexIterator const &amp;a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>operator*</name>
      <anchorfile>classapi_1_1_index_iterator.html</anchorfile>
      <anchor>a89b9326bd1b0883dd69559cc962b4480</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classapi_1_1_index_iterator.html</anchorfile>
      <anchor>a386139ae5017b8b0c644365aa51faaea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>IndexIterator &amp;</type>
      <name>operator--</name>
      <anchorfile>classapi_1_1_index_iterator.html</anchorfile>
      <anchor>ac1ec402f7bc97f7f0676a08f1af1828d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::PrivateExecutionContext</name>
    <filename>classapi_1_1_private_execution_context.html</filename>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>is_error</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>ae3b8276f62d5ee5bbfee85488401a8d2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>is_success</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>a1fd0a868e3525553f263d4c7bd77e342</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>value</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>aac5f93f5788bcbf12f6058aefbaf309b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>size_t</type>
      <name>context_count</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>ae602dc8d1128e7871cc5f33066d1b50f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Error &amp;</type>
      <name>get_error</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>a7c8ca383668a4956c0f1b07ababd73d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>free_context</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>afff1f7cb1ba25d4d04399a515a4febc9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>update_error_context</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>a95cdab4e4b55c1ca07ad6c23d47cdbc9</anchor>
      <arglist>(int result, int line, const char *message)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>ExecutionContext</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>a3315573b644a9bc222a160963bdde2cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>ErrorGuard</name>
      <anchorfile>classapi_1_1_private_execution_context.html</anchorfile>
      <anchor>aece684bf8d8d23557e2da48457abbf93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::ProgressCallback</name>
    <filename>classapi_1_1_progress_callback.html</filename>
    <member kind="typedef">
      <type>bool(*</type>
      <name>callback_t</name>
      <anchorfile>classapi_1_1_progress_callback.html</anchorfile>
      <anchor>a608461fe809da5f78759451bdee3024b</anchor>
      <arglist>)(void *, int, int)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ProgressCallback</name>
      <anchorfile>classapi_1_1_progress_callback.html</anchorfile>
      <anchor>a14b1114430ee1c1cce62c58ba7349d77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>update</name>
      <anchorfile>classapi_1_1_progress_callback.html</anchorfile>
      <anchor>ad5088dff96b7e7a5a2a2fa9f824d0e02</anchor>
      <arglist>(int value, int total) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>indeterminate_progress_total</name>
      <anchorfile>classapi_1_1_progress_callback.html</anchorfile>
      <anchor>a60052db8770421357afeabcc3f7ef104</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>update_function</name>
      <anchorfile>classapi_1_1_progress_callback.html</anchorfile>
      <anchor>a2d78bebf0cb67f0a50ad7207d827e092</anchor>
      <arglist>(const void *context, int value, int total)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::Range</name>
    <filename>classapi_1_1_range.html</filename>
    <templarg>typename Type</templarg>
    <member kind="function">
      <type>constexpr</type>
      <name>Range</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>abb90825c02c7c7dce59c0fb306f2e7a3</anchor>
      <arglist>(const Type &amp;start, const Type &amp;finish, typename RangeIterator&lt; Type &gt;::TransformCallback transform=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>begin</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>ab6e1013b2c446865ca6246366aadff90</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>begin</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>a074465da10e00d1fc43c364c7c4af551</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>end</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>a66f06b0c16b2c7dc87036fb00a31a03d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>end</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>ad93342ab4b9d4fdd6dff8d844c92279b</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>cbegin</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>aaa649fc95003c13aa2a96643fd791583</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator&lt; Type &gt;</type>
      <name>cend</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>a3ddeacb57e95ddc209137e6f2efe730e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Type</type>
      <name>forward</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>a7ff961fb05ef769f9f8d7d3c075fa632</anchor>
      <arglist>(const Type &amp;a, const Type &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Type</type>
      <name>reverse</name>
      <anchorfile>classapi_1_1_range.html</anchorfile>
      <anchor>a8cf14f8f9f1f1e733238d1629a3d1a0d</anchor>
      <arglist>(const Type &amp;a, const Type &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::RangeIterator</name>
    <filename>classapi_1_1_range_iterator.html</filename>
    <templarg>typename Type</templarg>
    <member kind="typedef">
      <type>Type(*)(const Type &amp;, const Type &amp;)</type>
      <name>TransformCallback</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>ab13fd4b5ed1820d632f1aa5eb57c7ff8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RangeIterator</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>adee5bf2a01059a1ba999586cf0eac673</anchor>
      <arglist>(Type value, Type max, TransformCallback transform)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>af0fa06c256fa2924bdd70dbda070fc76</anchor>
      <arglist>(RangeIterator const &amp;a) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>operator*</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>adef110f94ad7913550f7270abd8c3a69</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator &amp;</type>
      <name>operator++</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>a38bba9c8af88d8b793e6e3fe90362dc9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RangeIterator &amp;</type>
      <name>operator--</name>
      <anchorfile>classapi_1_1_range_iterator.html</anchorfile>
      <anchor>a3cb030dec5f6a81eb3f0a37a44a242e9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>api::ThreadExecutionContext</name>
    <filename>classapi_1_1_thread_execution_context.html</filename>
    <member kind="function">
      <type></type>
      <name>~ThreadExecutionContext</name>
      <anchorfile>classapi_1_1_thread_execution_context.html</anchorfile>
      <anchor>a48a03837aaa8b22abfb5d08daafc5778</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::ClockTime</name>
    <filename>classchrono_1_1_clock_time.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ClockId</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>af459a6b32ddf83990c3c791486e32dcf</anchor>
      <arglist></arglist>
      <enumvalue file="classchrono_1_1_clock_time.html" anchor="af459a6b32ddf83990c3c791486e32dcfa37e2a166d3ab28426a1d1a481d356d33">realtime</enumvalue>
    </member>
    <member kind="typedef">
      <type>var::KeyString</type>
      <name>UniqueString</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a5b5b2d4f96914fc017984497379ff84c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ClockTime</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a7aa0c5c10b484fd999013a06e003f4f4</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ClockTime</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>aea99cd12b5902b78023b01f42332629e</anchor>
      <arglist>(const struct timespec &amp;nano_time)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ClockTime</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a40c61602367b1230f9b72134eea13b7f</anchor>
      <arglist>(const MicroTime &amp;micro_time)</arglist>
    </member>
    <member kind="function">
      <type>ClockTime &amp;</type>
      <name>reset</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a44faddcc7eb6aeedc4ac98418ea25d56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ClockTime &amp;</type>
      <name>set_seconds</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a5be122c837454319a64463c1228e0193</anchor>
      <arglist>(u32 seconds)</arglist>
    </member>
    <member kind="function">
      <type>ClockTime &amp;</type>
      <name>set_nanoseconds</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a3f3e1c37784bd56e777c959b409bf5db</anchor>
      <arglist>(u32 value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const struct timespec *</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>acfcf465ec8ef2096bb63ddeca4a21b70</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator struct timespec *</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a520da0fa2521a738de465d42e66af736</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ad176061bd97df42fcc28bcfcc6dfa55e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a245573bf5f9c610d80353fe4c05c0d15</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a0e1e8add8bfbdfa29f895c7cf5f1c01a</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a2f6925db3049f20c60902bee63bcec68</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ac506bb7e3983150c211e0c7927500f86</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a00716c695266354c89517903a49e6dbb</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>afcd8c6110f275a814f7465accbfa324d</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>operator+</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a38efe39d3d3a957bded8426a6972563a</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>operator-</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ad72f501a289726200ae4eb9ec6c6317c</anchor>
      <arglist>(const ClockTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>get_age</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ae305124c2f1369e4497233bfcc392dec</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ClockTime &amp;</type>
      <name>operator+=</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a328905bbe73be4f218c2cb8fb3d0c516</anchor>
      <arglist>(const ClockTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>ClockTime &amp;</type>
      <name>operator-=</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a7a581e19d97938c4e57d2fd2669abf5a</anchor>
      <arglist>(const ClockTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>s32</type>
      <name>seconds</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ad2992b1b20d1a55487d3f092ae11878d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>s32</type>
      <name>nanoseconds</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a6803603b5bcbcd1f54520fcdadedf29e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>UniqueString</type>
      <name>to_unique_string</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ace3e139c30a66f8f33f2bd9d2473751a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringClass</type>
      <name>to_string</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>ad214091c8c23bbcfb23b510fdea76e13</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>struct timespec *</type>
      <name>timespec</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a918ca2c9df3e763ac7c4a8fadce0d14d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const struct timespec *</type>
      <name>timespec</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>aa21f4c5a77bd436681fa63e5a08bc992</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator MicroTime</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a02b1438a0a07db6f22a770dd64db92f8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>get_system_time</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a40869380d8a678e7e5cff1c45f629173</anchor>
      <arglist>(ClockId clock_id=ClockId::realtime)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>get_system_resolution</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a05b56788c5af38df159c0fda2432bc59</anchor>
      <arglist>(ClockId clock_id=ClockId::realtime)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>from_seconds</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a9466e7e9a078592933e92169767e7745</anchor>
      <arglist>(u32 seconds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ClockTime</type>
      <name>invalid</name>
      <anchorfile>classchrono_1_1_clock_time.html</anchorfile>
      <anchor>a519ef2efe93fde295063040fbb92bb46</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::ClockTimer</name>
    <filename>classchrono_1_1_clock_timer.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="enumeration">
      <type></type>
      <name>IsRunning</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>aa5f5d554be40c1adb5bc07b1da5809cc</anchor>
      <arglist></arglist>
      <enumvalue file="classchrono_1_1_clock_timer.html" anchor="aa5f5d554be40c1adb5bc07b1da5809cca7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classchrono_1_1_clock_timer.html" anchor="aa5f5d554be40c1adb5bc07b1da5809ccaa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>ClockTimer</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a903e1adb48548e7d9e72b471daaac365</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ClockTimer</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>aee3c08eb70da73c260a91bf64b5b1726</anchor>
      <arglist>(IsRunning is_running)</arglist>
    </member>
    <member kind="function">
      <type>ClockTimer &amp;</type>
      <name>start</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a247aa32e0a7fedee6e4d646255dbbe39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ClockTimer &amp;</type>
      <name>restart</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>aca2d02f58c57415d38b0c580587f2a7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ClockTimer &amp;</type>
      <name>resume</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>ab5043ebe404fbfbb55a4aa5ce0a42c17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ClockTimer &amp;</type>
      <name>stop</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>aaf8db1b9fb793765098f6c9c6804c9ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ClockTimer &amp;</type>
      <name>reset</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a1854a9ec66a8b6748a87349ca410d848</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_running</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a8cc605cdba4890c6bee95be3711fd5a4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_started</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a95e6fd3752350754b6cde4e157201e33</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_stopped</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a06ee697d107959ef7f8bd2b1fa272cae</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_reset</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a9fd5192cb674d0f59c2210872fc46688</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>milliseconds</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>ae7aad9577e21d59db2ee6d7d14296c88</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>microseconds</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a585d980353866461cb2849acdd477786</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>seconds</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a8c6ef8d97fbd24ec9a91934e03c58668</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ClockTime</type>
      <name>clock_time</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a4139270fdd59472671ffb91129b71e18</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>micro_time</name>
      <anchorfile>classchrono_1_1_clock_timer.html</anchorfile>
      <anchor>a26b402e4cce1c9d75e449adfe74a37a9</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::Date</name>
    <filename>classchrono_1_1_date.html</filename>
    <class kind="class">chrono::Date::Construct</class>
    <member kind="enumeration">
      <type></type>
      <name>Month</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>abe722ad596ba154c4d634a4802dd69e4</anchor>
      <arglist></arglist>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a467b6140fe3bb958f2332983914de787">january</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a8eb8e307a6d649bc7fb51443a06a216f">february</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a4061838f4395ef541fb1b3f07e42bc21">march</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a37d153a06c79e99e4de5889dbe2e7c57">april</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a9a4b6f884971dcb4a5172876b335baab">may</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a11501255f17710952e79563ddc090a4d">june</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a3785a4f12840727f9fc71676c104ac0d">july</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a61a590f1b9b5548efbae70fd7bcf45b3">august</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a110cea74cf52e41ead691dccdf75f27b">september</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4ae60a95f3f443e37f5a47210d9b340a05">october</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4a4d04cedd6d05b1f16a4404ff5a1fa4af">november</enumvalue>
      <enumvalue file="classchrono_1_1_date.html" anchor="abe722ad596ba154c4d634a4802dd69e4af962bed5616612c8c7053f6e97e72b12">december</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>Date</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a201e73167fab5756fdd4ac2682e3ab45</anchor>
      <arglist>(const DateTime &amp;date_time, const Construct &amp;options=Construct())</arglist>
    </member>
    <member kind="function">
      <type>var::GeneralString</type>
      <name>to_string</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a5f53d576eca04edba73f807ec0ff5f47</anchor>
      <arglist>(var::StringView format=&quot;%Y-%m-%d %H:%M:%S&quot;) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>second</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>ade4c86ad17b42dea3f1aa1df9fd0cd03</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>minute</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a95efd68bc6b29c6ea4bece0c1e34f4ec</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>hour</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a6ba0feba35906fb89d3854433cd90f68</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>day</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a8690d8bb9d5757c7ceb7378d823a8f8b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>weekday</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a257bb6468c65463d14f678f131d5a9b8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>yearday</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a6006338a2398a303e2208f0898da7391</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Month</type>
      <name>month</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a6b9fe2d7a7ca5bbedf12b8c921747aeb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>year</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a23751ddb2eb98b1adc2fec04c30de01b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const struct tm &amp;</type>
      <name>get_tm</name>
      <anchorfile>classchrono_1_1_date.html</anchorfile>
      <anchor>a9710397d1b1908088d563667b920e760</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::Date::Construct</name>
    <filename>classchrono_1_1_date_1_1_construct.html</filename>
    <member kind="function">
      <type></type>
      <name>Construct</name>
      <anchorfile>classchrono_1_1_date_1_1_construct.html</anchorfile>
      <anchor>afef37e03197ca1d81e0672c8b7858387</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::DateTime</name>
    <filename>classchrono_1_1_date_time.html</filename>
    <class kind="class">chrono::DateTime::Construct</class>
    <member kind="function">
      <type></type>
      <name>DateTime</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>ae8b7ce7730a057c7546dc8a9d3fb4560</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DateTime</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>ad2dcf0ab2a9e1b508ec00188b21e3bff</anchor>
      <arglist>(time_t t)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DateTime</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a2770828a8b5be247609520f908150ee9</anchor>
      <arglist>(const Construct &amp;options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DateTime</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>acd66d2e15a27ad2735d91afde40f8131</anchor>
      <arglist>(MicroTime t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a9e448b7571fd7b6613032aa0f940d505</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DateTime</type>
      <name>operator+</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a717fc32f124624eaeed087430bbdaa19</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>DateTime</type>
      <name>operator-</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>abc625266c073d7d9be7589a846bf961d</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>aec9b4bc2286dd3047a34b23abc5b8999</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>aed4a2a40144ea79577da8a38ba4c299e</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a627a9a37fa4b2766e0f276623acb921c</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a057ea3431c9a5660c5c801557c9cddc8</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>ac19cb5556c63203c7a838a0d0694fd0c</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a4bec9fc213128c7c2c4d53966c9b8734</anchor>
      <arglist>(const DateTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>DateTime</type>
      <name>age</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a02e2135651d073df6ad2df8aa9ee1c37</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DateTime &amp;</type>
      <name>operator+=</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a2408d95a022394bbd3fa991a4b507265</anchor>
      <arglist>(const DateTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>DateTime &amp;</type>
      <name>operator-=</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a8e3cec7993dee5ea34140acdd99bb2f2</anchor>
      <arglist>(const DateTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>DateTime &amp;</type>
      <name>set_system_time</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>af4f483d283b493c9c50bd84e91add3bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>DateTime &amp;</type>
      <name>set_time</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a1d9fe1d2a4ac871560630820f00c5ea7</anchor>
      <arglist>(time_t tm)</arglist>
    </member>
    <member kind="function">
      <type>time_t</type>
      <name>ctime</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a5b774779935fb992fce139571959440f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>second</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>ac105e41f7b76c27e8d94fbbbc19da553</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>minute</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>aedaafdfb748642ffaa5e549e1251a71b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>hour</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>a4f84d8139c2a592fcc81478680fe02cb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static DateTime</type>
      <name>get_system_time</name>
      <anchorfile>classchrono_1_1_date_time.html</anchorfile>
      <anchor>aa0ffff493ede8e1ba9ffab94f4c6d870</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::DateTime::Construct</name>
    <filename>classchrono_1_1_date_time_1_1_construct.html</filename>
    <member kind="function">
      <type></type>
      <name>Construct</name>
      <anchorfile>classchrono_1_1_date_time_1_1_construct.html</anchorfile>
      <anchor>a14d073a849254467b4f9f4c053049b23</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::MicroTime</name>
    <filename>classchrono_1_1_micro_time.html</filename>
    <member kind="function">
      <type></type>
      <name>MicroTime</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a06652408d9d68e79b308815c3c9722a6</anchor>
      <arglist>(u32 microseconds=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a595ca3536b3bcb992d24524f25be71f6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime &amp;</type>
      <name>operator+=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>ac0b69efe870edadcc06863bfd53e7a37</anchor>
      <arglist>(const MicroTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime &amp;</type>
      <name>operator-=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>ac6418183baab2e78c9a8e250e76a5f26</anchor>
      <arglist>(const MicroTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime &amp;</type>
      <name>operator*=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a3076b1b598d334325d5088edd31e4953</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime &amp;</type>
      <name>operator/=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a36f8a6797cef5272cf3e6a7a2a5e04b7</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator+</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a93204aaad183141c8c4cf32b96c44c91</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator*</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a1cedf4806b71fc501152971c3fd21f8e</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator/</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a6765324816dd65e4b6f4e8262a570e84</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator-</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a54740396f25931109d7418a8544d17f9</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a1527b9a2ddee00bafe3621542b3863dc</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a386204f7e42f29034f2e1700798cc719</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a149bb511533b6b076cc7e61c3a07aa79</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a411a5167ae2a386947e2718fbb6a7803</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>ae6a067b37f8d13c254d3a4671543d249</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a629f576cfa52a169e589e4acf7d9e828</anchor>
      <arglist>(const MicroTime &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>seconds</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a56ee1ed58a2ce574fd44d8cec4cc4248</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>micro_time_t</type>
      <name>microseconds</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a933c83ddf3b7ced096809b4c0ea88c47</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>milliseconds</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a77554baa45c5d40bce7fa5f8deeb7afb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const MicroTime &amp;</type>
      <name>wait</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>aef40c80b0def48a36501200a92017cee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>MicroTime &amp;</type>
      <name>wait</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a2baa022f98e03e5975ba764bc309026f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static MicroTime</type>
      <name>invalid</name>
      <anchorfile>classchrono_1_1_micro_time.html</anchorfile>
      <anchor>a4b3a62498b03fb2359d6ca549aa782b8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>chrono::PerformanceScope</name>
    <filename>classchrono_1_1_performance_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>PerformanceScope</name>
      <anchorfile>classchrono_1_1_performance_scope.html</anchorfile>
      <anchor>a5cec6dbdbee9f6b30fcb263401774918</anchor>
      <arglist>(var::StringView name, const ClockTimer &amp;timer, printer::Printer &amp;printer)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PerformanceScope</name>
      <anchorfile>classchrono_1_1_performance_scope.html</anchorfile>
      <anchor>aa658c916988eed7d1683f4d4c32f5e01</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::Access</name>
    <filename>classfs_1_1_access.html</filename>
    <base>fs::FileInfoFlags</base>
    <member kind="function">
      <type></type>
      <name>Access</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a9782655270293dcb5b2d25625f6b8670</anchor>
      <arglist>(AccessFlags access=AccessFlags::read_ok|AccessFlags::write_ok|AccessFlags::file_ok|AccessFlags::execute_ok)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a47ed2764e8c09d8fbafcc651d13d705a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_write_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a849a67305c6eecebe1a8649042d4a0b6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_file_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a6160ebc7c38aa85348bf33264c1444bc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_execute_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a14ffb88b7d0b8422cdb20aa9398faad9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Access &amp;</type>
      <name>set_read_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>af722922da2198f69b5a542d74d83aed7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Access &amp;</type>
      <name>set_write_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a3a8a9dbc6a674c2157b6729d50a39676</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Access &amp;</type>
      <name>set_file_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a2513cccc388bc47bd31cfc7d7145f8db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Access &amp;</type>
      <name>set_execute_ok</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a1f09745ee28f2cc809d6e102772538d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>AccessFlags</type>
      <name>o_access</name>
      <anchorfile>classfs_1_1_access.html</anchorfile>
      <anchor>a33aff34b2f740defd55e06276a3bfcd1</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::Aio</name>
    <filename>classfs_1_1_aio.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="typedef">
      <type>var::Vector&lt; struct aiocb * &gt;</type>
      <name>AiocbList</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ac5c208c859b64cc626bfe98e481d98fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Aio</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a74204e8c98038bcaf5d6b9b181dcff9e</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Aio</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ab98c664e26bcc180c8c931a8834d40a8</anchor>
      <arglist>(var::View view, off_t location=0)</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>suspend</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ae5e64b53e410899ed2bc33f43618a506</anchor>
      <arglist>(const chrono::MicroTime &amp;timeout=chrono::MicroTime(0))</arglist>
    </member>
    <member kind="function">
      <type>volatile void *</type>
      <name>buffer</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a20758b5d5e3ca0298dc292cf15eea289</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>refer_to</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>aa90d614baca3bde4fee8192ea6e459fa</anchor>
      <arglist>(var::View item)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>nbytes</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>af485d75a8b3458e0343ad2fb045503e1</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>offset</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a79b13c689c400e07b21693f5f653d0cb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>set_offset</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>aeb8eb584a1c2a682e784ae2d4f17767b</anchor>
      <arglist>(int offset)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ret</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a82cc2d9fa2ce223e18348fe5a3e4c79e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>error</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a34cff9a3e93992957491372841a5da2e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_done</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ae59054581ae64f39bb11dfb0f050bde2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_busy</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a5b6a0afa6be00901f4b5cd9c8cb72e78</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>set_signal</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a50752590f126c94b365fd7c4d876708a</anchor>
      <arglist>(int number, int value)</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>set_signal_number</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>a8c7ca960881de44da23d97d842542b88</anchor>
      <arglist>(int number)</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>set_signal_value</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ab39354f9f68dc9e3e3b72ad713a22025</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function">
      <type>Aio &amp;</type>
      <name>set_location</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ad5c5ee52a40e66a2cef3a9d1fa52307c</anchor>
      <arglist>(int location)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>suspend</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>ae085f519d9b8cf3199a4f3cb6c10b509</anchor>
      <arglist>(const AiocbList &amp;list, const chrono::MicroTime &amp;timeout=chrono::MicroTime(0))</arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>hal::DeviceObject</name>
      <anchorfile>classfs_1_1_aio.html</anchorfile>
      <anchor>adcc43e44268a94a6a89c1b7606921276</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::DataFile</name>
    <filename>classfs_1_1_data_file.html</filename>
    <base>FileAccess&lt; DataFile &gt;</base>
    <member kind="function">
      <type></type>
      <name>DataFile</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>afc6679f53c25ff069f755a2c226a75c5</anchor>
      <arglist>(DataFile &amp;&amp;file)=default</arglist>
    </member>
    <member kind="function">
      <type>DataFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a5d0ce088d381a9a0e6420ce90cc08f23</anchor>
      <arglist>(DataFile &amp;&amp;file)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DataFile</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a41dbb6693afbd117f11a965676e028b9</anchor>
      <arglist>(const OpenMode &amp;flags=OpenMode::append_read_write())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DataFile</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>abfd891482c9dbbb80c16a76ccd83e757</anchor>
      <arglist>(const FileObject &amp;file_to_load)</arglist>
    </member>
    <member kind="function">
      <type>DataFile &amp;</type>
      <name>reserve</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a2edf70aad27516262fb63e0488df3ca2</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>DataFile &amp;</type>
      <name>resize</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a87194ab7b857e1105141c33efc611d4d</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>DataFile &amp;</type>
      <name>copy</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a6e4018de1f6bc16f299feb5708767c85</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>DataFile &amp;</type>
      <name>set_flags</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a89e6a6527d9ae4e62f246c9b95ba58fa</anchor>
      <arglist>(OpenMode open_flags)</arglist>
    </member>
    <member kind="function">
      <type>const OpenMode &amp;</type>
      <name>flags</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a67201836f07a83346716249bedf5ca42</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const var::Data &amp;</type>
      <name>data</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>a10391953749b869f71df16a915c2f484</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::Data &amp;</type>
      <name>data</name>
      <anchorfile>classfs_1_1_data_file.html</anchorfile>
      <anchor>ad2aa2da0b1930dc74841371c08f941d2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::Dir</name>
    <filename>classfs_1_1_dir.html</filename>
    <base>DirAccess&lt; Dir &gt;</base>
    <member kind="function">
      <type></type>
      <name>Dir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a8e69af82b22a095f9833ff95c6110ec6</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Dir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>aac3135d9b9e1c55242027044c034ccbb</anchor>
      <arglist>(const Dir &amp;dir)=delete</arglist>
    </member>
    <member kind="function">
      <type>Dir &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a28c1db9b1289653d7657d14123976bce</anchor>
      <arglist>(const Dir &amp;dir)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Dir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a203d9f406f9fb02eba31becac0944121</anchor>
      <arglist>(Dir &amp;&amp;dir) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Dir &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>ac50313b3387585c635efcdd90c1ec6ac</anchor>
      <arglist>(Dir &amp;&amp;dir)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Dir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a67f7405aa8202fcad98355585c9fa623</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_open</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>aced0a5a5b8faa0ddecf636c1a300c048</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>count</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a43aa6fa476d38c73a8557bec6a87dd67</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Dir &amp;</type>
      <name>open</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a220c8ca15d8efd66d247e81e7a56dfa7</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Dir &amp;</type>
      <name>close</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a450fa66bbefe90e39ac202cbb9cef2d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_readdir_r</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>aa7be8a2b54b9f354d3b96b99be990fbb</anchor>
      <arglist>(dirent *result, dirent **resultp) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_telldir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>acceba11d10374cd85fd074023f7ff598</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>interface_seekdir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>a69dcbb1a130c6f7d1ef84e1c78335ed9</anchor>
      <arglist>(size_t location) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>interface_rewinddir</name>
      <anchorfile>classfs_1_1_dir.html</anchorfile>
      <anchor>ab08f7bdf91a65ffda0b046f237bcb779</anchor>
      <arglist>() const override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::DirAccess</name>
    <filename>classfs_1_1_dir_access.html</filename>
    <templarg>class Derived</templarg>
    <base>fs::DirObject</base>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>rewind</name>
      <anchorfile>classfs_1_1_dir_access.html</anchorfile>
      <anchor>a0b2d97c199ef10da3fe5f579047b59ba</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>rewind</name>
      <anchorfile>classfs_1_1_dir_access.html</anchorfile>
      <anchor>a72e6de964534ef853bd628cb8fa939d2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_dir_access.html</anchorfile>
      <anchor>a9817bb0e9bc0d5a35ac39a9bd2e46e00</anchor>
      <arglist>(size_t location) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_dir_access.html</anchorfile>
      <anchor>a2b321180a74bc767fd5cf9f43de35b08</anchor>
      <arglist>(size_t location)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::DirObject</name>
    <filename>classfs_1_1_dir_object.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="enumeration">
      <type></type>
      <name>IsRecursive</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a3895c77a098308ba302d5fb3b7502fc9</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_dir_object.html" anchor="a3895c77a098308ba302d5fb3b7502fc9a7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classfs_1_1_dir_object.html" anchor="a3895c77a098308ba302d5fb3b7502fc9aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>DirObject</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a0a8cf350484d1da42079f49f7e2b33ab</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DirObject</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>ace6ff62343ce3fb5ec6e80af08f93dad</anchor>
      <arglist>(const DirObject &amp;dir)=delete</arglist>
    </member>
    <member kind="function">
      <type>DirObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a2d4aaaa44605f7d48b0b5b6c18876060</anchor>
      <arglist>(const DirObject &amp;dir)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DirObject</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a69a7799f7eab9fbbefb1ed98352c6a2d</anchor>
      <arglist>(DirObject &amp;&amp;dir)=default</arglist>
    </member>
    <member kind="function">
      <type>DirObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a131a235447a8fb06ccf24b077210cf80</anchor>
      <arglist>(DirObject &amp;&amp;dir)=default</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>read</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a10f48d15fd5a20ed5d5b2fea194d27f9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::PathString</type>
      <name>get_entry</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>adc3cbfdebf52c1b192f09fe03374bcea</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>entry_name</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a9131c305be3b758b8a44b097c752b0e2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ino</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>af4e21b83aa68e726e134b65e82032489</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>count</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a088889c83467da3fa987980ce60f9364</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const DirObject &amp;</type>
      <name>rewind</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a84bbbdd93d1ec5ed8e1b8d40a6397f25</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>DirObject &amp;</type>
      <name>rewind</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>ae43e3b2c3a208a57ce549a9594c34403</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const DirObject &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a52514e2c2c610db44d348c8dc2f52c29</anchor>
      <arglist>(size_t location) const</arglist>
    </member>
    <member kind="function">
      <type>DirObject &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a5151c3df8280f4e5be240d973fd82537</anchor>
      <arglist>(size_t location)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>tell</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>adf0ff46667f9a311aa221727d355d601</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const var::PathString &amp;</type>
      <name>path</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a6ce47eea4cfa73c68e4e18fd645a7e6a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::PathString</type>
      <name>filter_hidden</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a11d950292f00a2c3341f0e98a6737a55</anchor>
      <arglist>(const var::PathString &amp;entry)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_path</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a55fd71c8e7c3ed96d6acc29ed8f4785e</anchor>
      <arglist>(const var::StringView path)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_readdir_r</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a9cf0d16ae1f40dcd2eed25d363282fb5</anchor>
      <arglist>(dirent *result, dirent **resultp) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_telldir</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>ac909ef634868fc5f21b6137f17075964</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>interface_seekdir</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a6203cf3e365076d2c85df84fe40465f8</anchor>
      <arglist>(size_t location) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>interface_rewinddir</name>
      <anchorfile>classfs_1_1_dir_object.html</anchorfile>
      <anchor>a35c00cb79ac4a8166972979a2edccb3b</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::File</name>
    <filename>classfs_1_1_file.html</filename>
    <base>FileAccess&lt; File &gt;</base>
    <class kind="class">fs::File::DescriptorScope</class>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>af7d6182d340e521380d9794226405831</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a71d531ac13c26ef2f2396afa5ebcc95e</anchor>
      <arglist>(var::StringView name, OpenMode flags=OpenMode::read_only())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>ad124b6edd0439c74bc5e697403213eed</anchor>
      <arglist>(IsOverwrite is_overwrite, var::StringView path, OpenMode flags=OpenMode::read_write(), Permissions perms=Permissions(0666))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>abb445188c17a3b383876838f763e0024</anchor>
      <arglist>(const File &amp;file)=delete</arglist>
    </member>
    <member kind="function">
      <type>File &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a718c06a0a3ee2b72b3ba5f40d764e596</anchor>
      <arglist>(const File &amp;file)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a7e7c7d079f26c936aa5da075082a3825</anchor>
      <arglist>(File &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>File &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>ad249f6ff42ed2496c6b1593a5d558fe6</anchor>
      <arglist>(File &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~File</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a2d05886d61c7fc541de518e769a8d2a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>af6ce90a8246601c26792e484245988e5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>fileno</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>ab2a87afc985918679a674a2ee738a0b0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>flags</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a2ebe40b371b5948bbe518068c0b79e6d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>File &amp;</type>
      <name>set_fileno</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>ac9f42bbb278e49d5852894320dee272a</anchor>
      <arglist>(int fd)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_lseek</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>aa7dcf0a7e89531915df8db13d9939f03</anchor>
      <arglist>(int offset, int whence) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_read</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a8dc8bd30470c2342a6863d86a2818a4e</anchor>
      <arglist>(void *buf, int nbyte) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_write</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a0a7981bd9c3ffbf0ca831af1be19a57f</anchor>
      <arglist>(const void *buf, int nbyte) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_ioctl</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a19e2223323d24472ebcf6388306542b4</anchor>
      <arglist>(int request, void *argument) const override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_fsync</name>
      <anchorfile>classfs_1_1_file.html</anchorfile>
      <anchor>a5bcd9b96003d30077d4f4ffb8862cfc6</anchor>
      <arglist>() const override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::File::DescriptorScope</name>
    <filename>classfs_1_1_file_1_1_descriptor_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>DescriptorScope</name>
      <anchorfile>classfs_1_1_file_1_1_descriptor_scope.html</anchorfile>
      <anchor>ad85d773aca40f8be7774363724829672</anchor>
      <arglist>(File &amp;file, int file_descriptor)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DescriptorScope</name>
      <anchorfile>classfs_1_1_file_1_1_descriptor_scope.html</anchorfile>
      <anchor>ad8122fcecb4e8667134b85642fc06795</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileAccess</name>
    <filename>classfs_1_1_file_access.html</filename>
    <templarg>class Derived</templarg>
    <base>fs::FileObject</base>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a0d8277ad45ad2466fa617041eef28af3</anchor>
      <arglist>(void *buf, size_t size) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a1bac8e8fbc2db6a0a297515c5dac9cee</anchor>
      <arglist>(void *buf, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a4c8fd069ce022ee2c9ea87627455a90c</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a24db80aa448d5024054f69de2a8575ab</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>add4c17c096c6b42cf5a3a8e7ccf98892</anchor>
      <arglist>(const void *buf, size_t size) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a76d72d108f14a9045761520e2111779c</anchor>
      <arglist>(const void *buf, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>aac7b500c9230fc0405c455a1e039609d</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>aee4bb4e627d42743931b87b0de2f19f3</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>sync</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a08175d6e4283fa4fbfeb2ded6f4bc365</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>sync</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>ad53c24025903e57f692ddcc7bdb3dd79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a610cd5f38513a7340f01ab8425f5e358</anchor>
      <arglist>(const FileObject &amp;source_file, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>aa139f5528704671abd2497581de49a9c</anchor>
      <arglist>(const FileObject &amp;source_file, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a138febb11720818550afca4c554e82f3</anchor>
      <arglist>(const FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>afdb69ceb7d43dadb55b1042fe64ab73d</anchor>
      <arglist>(const FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>aebc3eb3be9d3229f69020dee6fd07a4b</anchor>
      <arglist>(int location, Whence whence=Whence::set) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a87d1ded5e914ba3e73f3df2974259f60</anchor>
      <arglist>(int location, Whence whence=Whence::set)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a94af4b4a41f705e1d0d3873f299aa4af</anchor>
      <arglist>(int request, void *arg) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a304ebf21ae0c63f529eff4a190512f2c</anchor>
      <arglist>(int request, void *arg)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a5a77d9b0bb05c41e10671f20b4a9529a</anchor>
      <arglist>(const Ioctl &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>ac2c548eb665b9831793755cd35720499</anchor>
      <arglist>(const Ioctl &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;&amp;</type>
      <name>move</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>a0811c2b6a99e481ace8940e28d473b8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>FileAccess</name>
      <anchorfile>classfs_1_1_file_access.html</anchorfile>
      <anchor>aff7dfba1226d7dedf86506aaad53d0a8</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileInfo</name>
    <filename>classfs_1_1_file_info.html</filename>
    <base>fs::OpenMode</base>
    <member kind="function">
      <type></type>
      <name>FileInfo</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a05ce1f5ff9b1bc86cef2bc9f3a5291c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileInfo</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a58fbb36e60de6153fc1886382a4845bc</anchor>
      <arglist>(const struct stat &amp;st)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a977c89f18708de7cb5841cb195b09bcd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_directory</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>aff29435b1e45f1dab904de33521c8447</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_file</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>aae2483d37d8ad701e8b782da75bb7afa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_device</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a2a86c367fbfbbd455c75fa86c4d250ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_block_device</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>adfd136047aba7b19e97e177e4bca2ea2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_character_device</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a86ec97e6d663b962e13a95bfc2fca724</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_socket</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>abed4008250cde0cd3f65072b35ae1cb0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_fifo</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>ab1967a23b3d0062825c89c729edf72a2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>size</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>a28ec6f20d6af2c02fe158e632ae13446</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Permissions</type>
      <name>permissions</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>ae12aca6f37623c42084f3c58c351bfbb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>owner</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>ad028afe664ceb9c62d08b943d266d7eb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>group</name>
      <anchorfile>classfs_1_1_file_info.html</anchorfile>
      <anchor>ac84002664fbf37de37ec3359ef2a85b5</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileInfoFlags</name>
    <filename>classfs_1_1_file_info_flags.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>PermissionFlags</name>
      <anchorfile>classfs_1_1_file_info_flags.html</anchorfile>
      <anchor>aab8959020c647fca0f3d80e0101b5abf</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa334c4a4c42fdb79d7ebc3e73b517e6f8">none</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa55f10ee6662bd4b0bab750c3300e25eb">public_execute</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa5ae385d83948e8999909cd4ff6286eb9">public_write</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa4c9a48a0e0797d75b7ed0bcc43d6472d">public_read</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa81f3cb47e7927b141c1b7639b8a59e79">group_execute</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfacf5f2e0341d3d21a4bc073c8eb8a25fa">group_write</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa25103dc0b7bf4bb70a12fdc9ae83b5dc">group_read</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa873db9455356e7092827b83f9321bde6">owner_execute</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa0d521a25ebf962a812b43c32fe36500e">owner_write</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aab8959020c647fca0f3d80e0101b5abfa13804bd89bd86850b7c1b3cf17148c8b">owner_read</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>OpenFlags</name>
      <anchorfile>classfs_1_1_file_info_flags.html</anchorfile>
      <anchor>a79f31ab4b6deb27ede7b26193adb5c1d</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1dabefe72871b2de8f4f0e20108517e31fe">read_only</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da2629564984b808cf7e6cfc61a0286d69">write_only</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da76ea0bebb3c22822b4f0dd9c9fd021c5">create</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da244f58cf07c35fd48d7524b289551e5c">truncate</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da9516dfb15f51c7ee19a4d46b8c0dbe1d">append</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1daa4293995cfbfa9ce60ce71ade2ff75f7">exclusive</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da06ad287ea83b37a6f9db3d8d10d72c8f">read_write</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da3c092d5dc073f08bb2581754f9f963dd">non_block</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1dab2bd912bf8e8e1247f8627077b07400f">no_delay</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da9d7183f16acce70658f686ae7f1a4d20">binary</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="a79f31ab4b6deb27ede7b26193adb5c1da29a9fc71e0dc5ee18c2380d9a20ea68f">access_mode</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>AccessFlags</name>
      <anchorfile>classfs_1_1_file_info_flags.html</anchorfile>
      <anchor>aa8c8d5b66e54b777f3d1ada3d0197930</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aa8c8d5b66e54b777f3d1ada3d0197930a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aa8c8d5b66e54b777f3d1ada3d0197930ab5362b654caf03a3d5ef7d1e426c3ed0">read_ok</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aa8c8d5b66e54b777f3d1ada3d0197930a0b75e4e2fe94de85cb1ef0851efb433f">write_ok</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aa8c8d5b66e54b777f3d1ada3d0197930a19788befbae099c98130488c723a627c">execute_ok</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="aa8c8d5b66e54b777f3d1ada3d0197930a7b5a62d9ec43064ee9692271e8641bb8">file_ok</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>TypeFlags</name>
      <anchorfile>classfs_1_1_file_info_flags.html</anchorfile>
      <anchor>ad1f26cc0bce96368db7bd5c4d5b59704</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704af2ce11ebf110993621bedd8e747d7b1b">mask</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704aaf37d08ae228a87dc6b265fd1019c97d">regular</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704aa956161a69928cd130a889b88082fb6e">character</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704a5f8f22b8cdbaeee8cf857673a9b6ba20">directory</enumvalue>
      <enumvalue file="classfs_1_1_file_info_flags.html" anchor="ad1f26cc0bce96368db7bd5c4d5b59704acf54937a2330ac17aa523bf7130911a3">fifo</enumvalue>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileMemberAccess</name>
    <filename>classfs_1_1_file_member_access.html</filename>
    <templarg>class Derived</templarg>
    <member kind="typedef">
      <type>fs::FileObject::Whence</type>
      <name>Whence</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a2d21dd7e13a5877e720ff44c6953c57c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>fs::FileObject::Write</type>
      <name>Write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a5a99f538fff1bcaf24e8b5f24b418a99</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>fs::FileObject::Ioctl</type>
      <name>Ioctl</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a45331ef50f80bab68146ef60a9012ce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileMemberAccess</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>ae1d1027e243da9a386aea1e154dc758a</anchor>
      <arglist>(const fs::FileObject &amp;file)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a37446240d71ca214d70b7313835c6a68</anchor>
      <arglist>(void *buf, size_t size) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a762d0aab7a5261babbb7f2d7af6c9986</anchor>
      <arglist>(void *buf, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a0c10be395adff855a5f1860c72702f9c</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a1adc9ee73ccf9326a4f60dde271c5c6d</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>ab4720cba059f67e49f4ea88099ff2abf</anchor>
      <arglist>(const void *buf, size_t size) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>ac400a26416f520cb6b38c936af540698</anchor>
      <arglist>(const void *buf, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a81a373261e743c1568dad3fc5d6f15e7</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a4de58baef7bdb427836d8ff5afec44af</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>ae9a9fa85fe1e7b4bb92b447062193071</anchor>
      <arglist>(const fs::FileObject &amp;source_file, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a9cee7b823de99fde4a9ef0010b2fbd43</anchor>
      <arglist>(const fs::FileObject &amp;source_file, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a8fd3f64553175be3db011c8237a65599</anchor>
      <arglist>(const fs::FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a3e1a8df33697ed06ea7049a4341caefb</anchor>
      <arglist>(const fs::FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a685964e8018ea9b70d9cf348ab6ae4a7</anchor>
      <arglist>(int location, Whence whence=Whence::set) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a98d3eeaf1236d40c310cbfe6e919d3ff</anchor>
      <arglist>(int location, Whence whence=Whence::set)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a267d64d4a12707c42ccfaea490f36542</anchor>
      <arglist>(int request, void *arg) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>ab4cb1d04d4bd9b0d1d8a4af47534c4b7</anchor>
      <arglist>(int request, void *arg)</arglist>
    </member>
    <member kind="function">
      <type>const Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a1daea3ef166305c0e491e4a42963d301</anchor>
      <arglist>(const Ioctl &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_member_access.html</anchorfile>
      <anchor>a640fc262611d14a5d79c7c93352fefa9</anchor>
      <arglist>(const Ioctl &amp;options)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileObject</name>
    <filename>classfs_1_1_file_object.html</filename>
    <base>api::ExecutionContext</base>
    <base>fs::FileInfoFlags</base>
    <class kind="class">fs::FileObject::Ioctl</class>
    <class kind="class">fs::FileObject::LocationGuard</class>
    <class kind="class">fs::FileObject::Verify</class>
    <class kind="class">fs::FileObject::Write</class>
    <member kind="enumeration">
      <type></type>
      <name>IsOverwrite</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a91df41f3f4682d9cb09c8ffe7bf5b6fe</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a91df41f3f4682d9cb09c8ffe7bf5b6fea7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a91df41f3f4682d9cb09c8ffe7bf5b6feaa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IsNull</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a67dc7666b7ba8c8b325138bdf882e7c0</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a67dc7666b7ba8c8b325138bdf882e7c0aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Whence</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a04217bfdda67e008ac4543e66c711b6b</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a04217bfdda67e008ac4543e66c711b6bacdaeeeba9b4a4c5ebf042c0215a7bb0e">set</enumvalue>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a04217bfdda67e008ac4543e66c711b6ba43b5c9175984c071f30b873fdce0a000">current</enumvalue>
      <enumvalue file="classfs_1_1_file_object.html" anchor="a04217bfdda67e008ac4543e66c711b6ba7f021a1415b86f2d013b2618fb31ae53">end</enumvalue>
    </member>
    <member kind="typedef">
      <type>LocationGuard</type>
      <name>LocationScope</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>aac91a36c9a958167926e7f12cb7e5503</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileObject</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a4f3943ab12b78a3d0462b0456fb4852d</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileObject</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a4e0b532fa654972f987b76553de2b3e8</anchor>
      <arglist>(const FileObject &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a73e297c21ad061ba34f187375b53337f</anchor>
      <arglist>(const FileObject &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileObject</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>abc9642a821aa2b9c63ac19e5ee427aeb</anchor>
      <arglist>(FileObject &amp;&amp;a)=default</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a1c6a4ef2b066354d938f316efe56d6e7</anchor>
      <arglist>(FileObject &amp;&amp;a)=default</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>size</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a65a2979f65847e45e639b160d474457c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>size_signed</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a6ffa543b59a25f2d79825ee59b696b5a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>location</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a47bf1de51cfbcc8ec10f1a2b6c685e8b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a0c266a254383d5148c4fcdbbc8c95aa0</anchor>
      <arglist>(void *buf, int size) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>aaefd003b44858eb6a7e097b636ac3ee6</anchor>
      <arglist>(void *buf, int size)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>aac6f4bac01ce5de70df85339f345bcb5</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>read</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a031880cf3de401a0e6f002fab12faf1e</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a900d46a46fa3a48d136acb055af4914a</anchor>
      <arglist>(const void *buf, int size) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a14b2b1b72b220f672d4757cc9df81f8a</anchor>
      <arglist>(const void *buf, int size)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a67c2c74ab9e4f706adee0751eb36e7b1</anchor>
      <arglist>(var::View view) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>acff3b0926805e37f06f671b64882cc8a</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a64ec5875ff221d8b9949009cb11f14c4</anchor>
      <arglist>(const FileObject &amp;source_file, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>verify</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>ad1f7c261534e382960445c4123232b84</anchor>
      <arglist>(const FileObject &amp;source_file, const Verify &amp;options=Verify()) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a0e887edee1476c33af621809270fc3e4</anchor>
      <arglist>(const FileObject &amp;source_file, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a91c452b7ec7b24e024dea417aa9acdfe</anchor>
      <arglist>(const FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write()) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a14030b880344ced4767c42bbce69717c</anchor>
      <arglist>(const FileObject &amp;source_file, const var::Transformer &amp;transformer, const Write &amp;options=Write())</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>af42d4f013a10955fdc08ba1c5abc18fa</anchor>
      <arglist>(int location, Whence whence=Whence::set) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>seek</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>ac1897b14da83a59661afe09734a1f2b6</anchor>
      <arglist>(int location, Whence whence=Whence::set)</arglist>
    </member>
    <member kind="function">
      <type>var::GeneralString</type>
      <name>gets</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>af985a8ed1bd87544758e1c35a2262709</anchor>
      <arglist>(char term=&apos;\n&apos;) const</arglist>
    </member>
    <member kind="function">
      <type>StringType</type>
      <name>get_line</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a047a56b83c755b87a40e527c65f6d505</anchor>
      <arglist>(char term=&apos;\n&apos;) const</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a51372d2e4e059ff61c02f056257bb5a7</anchor>
      <arglist>(int request, void *arg) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>ad8ba9dc1ef2b68c909314a4d70765e0e</anchor>
      <arglist>(int request, void *arg)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>aa53dc315b36882440db2ebe5bdbaa7ce</anchor>
      <arglist>(int request) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>adff5fda0af618c7ae7c3b19ab9c036b3</anchor>
      <arglist>(int request)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>aaebd946b8a5b745b1e679cab18a1aea7</anchor>
      <arglist>(const Ioctl &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a1500caf7d9309ed686e28b8de235a6c7</anchor>
      <arglist>(const Ioctl &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>const FileObject &amp;</type>
      <name>sync</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a75652fdef99aa7637ed6f7397535ad2f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FileObject &amp;</type>
      <name>sync</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a0f5f452ecd534b7ec4aea434b8dd870d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_lseek</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a5ce9ef2131a2e715ff0f5e39976f5cc5</anchor>
      <arglist>(int offset, int whence) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_read</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a09a12609d3d16becde8ace611a91dfcf</anchor>
      <arglist>(void *buf, int nbyte) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_write</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>abcde7c0571b2bf1dec9ea5f2480e6439</anchor>
      <arglist>(const void *buf, int nbyte) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual int</type>
      <name>interface_ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a1512640946f22552dbfc0ff397628d48</anchor>
      <arglist>(int request, void *argument) const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual int</type>
      <name>interface_fsync</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a60e8766bc95ea2f5672c47dab371b840</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>fake_seek</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>ae74e67b7592bdfbd9a02e1943dd34628</anchor>
      <arglist>(int &amp;location, size_t size, int offset, int whence)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static int</type>
      <name>fake_ioctl</name>
      <anchorfile>classfs_1_1_file_object.html</anchorfile>
      <anchor>a88365d1c6fbf5bc4c792996f2e167723</anchor>
      <arglist>(int request, void *argument)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileObject::Ioctl</name>
    <filename>classfs_1_1_file_object_1_1_ioctl.html</filename>
  </compound>
  <compound kind="class">
    <name>fs::FileObject::LocationGuard</name>
    <filename>classfs_1_1_file_object_1_1_location_guard.html</filename>
    <member kind="function">
      <type></type>
      <name>LocationGuard</name>
      <anchorfile>classfs_1_1_file_object_1_1_location_guard.html</anchorfile>
      <anchor>a744070026475cdb9ec0b1c04806729ac</anchor>
      <arglist>(const FileObject &amp;object)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LocationGuard</name>
      <anchorfile>classfs_1_1_file_object_1_1_location_guard.html</anchorfile>
      <anchor>ac87c3770af22ac9d737efa07855b1068</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileObject::Verify</name>
    <filename>classfs_1_1_file_object_1_1_verify.html</filename>
    <member kind="function">
      <type></type>
      <name>Verify</name>
      <anchorfile>classfs_1_1_file_object_1_1_verify.html</anchorfile>
      <anchor>ad4be98e7fb60a4d7faa92c0195679a89</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileObject::Write</name>
    <filename>classfs_1_1_file_object_1_1_write.html</filename>
    <member kind="function">
      <type></type>
      <name>Write</name>
      <anchorfile>classfs_1_1_file_object_1_1_write.html</anchorfile>
      <anchor>af77db8dd26bb0c616fb64ea32d0c74d2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileSystem</name>
    <filename>classfs_1_1_file_system.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">fs::FileSystem::Rename</class>
    <member kind="enumeration">
      <type></type>
      <name>IsExclude</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a4a0d5fb0636bbc1c24cc4807943db5fe</anchor>
      <arglist></arglist>
      <enumvalue file="classfs_1_1_file_system.html" anchor="a4a0d5fb0636bbc1c24cc4807943db5fea7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classfs_1_1_file_system.html" anchor="a4a0d5fb0636bbc1c24cc4807943db5feaa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="typedef">
      <type>File::IsOverwrite</type>
      <name>IsOverwrite</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a79e8659717e1d4c13425988eb9b364a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Dir::IsRecursive</type>
      <name>IsRecursive</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a6f880f407dd420fcfce9d24f36047c13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IsExclude(*)(const var::StringView name, void *)</type>
      <name>ExcludeCallback</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a4929836691293a0ed9f7f3e924a520f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FileSystem</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a1603c4b026d7f12e65c632ef0b94e146</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Access</type>
      <name>access</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ac92c98e236ef99109b7f8b769f88ff90</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exists</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a4f86db34f2d3b64254b7df0afdb70c2a</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>remove</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>abe514661b1e58bb4fc33a18ce0f04e79</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>remove_directory</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ab21c08309c37d9dd76a73d59adb0d8a1</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>remove_directory</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>afb5e68e00ec20cc94f6b8601881473ed</anchor>
      <arglist>(var::StringView path, IsRecursive recursive) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>directory_exists</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a718720879c308c3297921c44e115254f</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>create_directory</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a1ba20264c0d0d88c09f13302e61d2c18</anchor>
      <arglist>(var::StringView path, const Permissions &amp;permissions=Permissions(0)) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>create_directory</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>afd9ff6cd878212d156b7e3b73c1c328c</anchor>
      <arglist>(var::StringView path, IsRecursive is_recursive, const Permissions &amp;permissions=Permissions(0)) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>get_entry_count</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a8dc3402af3ed3d4a13864d84f5bf1606</anchor>
      <arglist>(var::StringView path, IsRecursive is_recursive=IsRecursive::no) const</arglist>
    </member>
    <member kind="function">
      <type>PathList</type>
      <name>read_directory</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a044ee4605fee04e68f558a1ea66241ed</anchor>
      <arglist>(var::StringView path, IsRecursive is_recursive=IsRecursive::no, ExcludeCallback exclude=nullptr, void *context=nullptr) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>rename</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ad3daefa8ab2afe5f098c35cec13ab28a</anchor>
      <arglist>(const Rename &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>operator()</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a35e584387189e2562a37d208214395bb</anchor>
      <arglist>(const Rename &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>const FileSystem &amp;</type>
      <name>touch</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a0042070b837d62f96c8d85b53959857b</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>FileInfo</type>
      <name>get_info</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a6b920f92f0445444b856cf2a5adbb6da</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function">
      <type>FileInfo</type>
      <name>get_info</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>af7659004f288c0a89263b929cf8be92e</anchor>
      <arglist>(const File &amp;file) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>access</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a40af8f0dca8289e7aadb462ca63ef522</anchor>
      <arglist>(var::StringView path, const Access &amp;access)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Permissions</type>
      <name>get_permissions</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ae6d429a7d1d1388920713f551deed9fd</anchor>
      <arglist>(var::StringView path) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_mkdir</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a0a9020e5ef88d4c3c3abad8a23dd48fd</anchor>
      <arglist>(const char *path, int mode) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_rmdir</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ae63d411dc5979d996242f6cd4a532106</anchor>
      <arglist>(const char *path) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_unlink</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>ad4aeaed4df7c0969d7583cb9502eacbe</anchor>
      <arglist>(const char *path) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_stat</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a6f48f407af18d93cd5bf0eb4caab4e6e</anchor>
      <arglist>(const char *path, struct stat *stat) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_fstat</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a175395a7566ae3c3ddcf858417fd705d</anchor>
      <arglist>(int fd, struct stat *stat) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>interface_rename</name>
      <anchorfile>classfs_1_1_file_system.html</anchorfile>
      <anchor>a435a4a278a86378aa09acf56e4b4c9b9</anchor>
      <arglist>(const char *old_name, const char *new_name) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::FileSystem::Rename</name>
    <filename>classfs_1_1_file_system_1_1_rename.html</filename>
  </compound>
  <compound kind="class">
    <name>fs::LambdaFile</name>
    <filename>classfs_1_1_lambda_file.html</filename>
    <base>FileAccess&lt; LambdaFile &gt;</base>
    <member kind="typedef">
      <type>int(*)(void *context, int location, var::View view)</type>
      <name>read_callback_t</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>ae28b9107a7ae0d38e142161c6461b843</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int(*)(void *context, int location, const var::View view)</type>
      <name>write_callback_t</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a759c9e8f0c5516eaba53cfd5390ed3f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LambdaFile</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a7326d926e470a7210d65a223901b4784</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LambdaFile</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>ae24cd52c28cb2f9e590b5b00975ec086</anchor>
      <arglist>(const LambdaFile &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>LambdaFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a455545515596adb04ffc30511c4bbf45</anchor>
      <arglist>(const LambdaFile &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LambdaFile</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a74468f5d33821f3d359ddd7ae8e08ec5</anchor>
      <arglist>(LambdaFile &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>LambdaFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a4c1f482e757e3480577026e68de6f2ab</anchor>
      <arglist>(LambdaFile &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>LambdaFile &amp;</type>
      <name>set_size</name>
      <anchorfile>classfs_1_1_lambda_file.html</anchorfile>
      <anchor>a2250ae39302627099701105a9003224e</anchor>
      <arglist>(size_t size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::NullFile</name>
    <filename>classfs_1_1_null_file.html</filename>
    <base>FileAccess&lt; NullFile &gt;</base>
    <member kind="function">
      <type></type>
      <name>NullFile</name>
      <anchorfile>classfs_1_1_null_file.html</anchorfile>
      <anchor>ae9c6472c9eeb9eb071708dcaa3f63831</anchor>
      <arglist>(size_t size=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NullFile</name>
      <anchorfile>classfs_1_1_null_file.html</anchorfile>
      <anchor>ab8ee2098a50f561e7e5cd32592d7f21a</anchor>
      <arglist>(const NullFile &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>NullFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_null_file.html</anchorfile>
      <anchor>a1c4dab4010128238e3bcfed138760710</anchor>
      <arglist>(const NullFile &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NullFile</name>
      <anchorfile>classfs_1_1_null_file.html</anchorfile>
      <anchor>a15673b74f57b9b155194cd37e27f9d45</anchor>
      <arglist>(NullFile &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>NullFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_null_file.html</anchorfile>
      <anchor>a761a358f7a97c18b1904c16e8ca15341</anchor>
      <arglist>(NullFile &amp;&amp;)=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::OpenMode</name>
    <filename>classfs_1_1_open_mode.html</filename>
    <base>fs::FileInfoFlags</base>
    <member kind="function">
      <type></type>
      <name>OpenMode</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>aaea5a754bc69d376da33d4f10ee21357</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OpenMode</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a274e29cafdc28e1f4bad9227a7b3579c</anchor>
      <arglist>(OpenFlags flags)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ad6de8b2940d251ce8503eb0d95ea4906</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_write_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ac1c5065cb0a3571ad809d59527aa828a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read_write</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ab340d3fb5406eae30983ce9b362dedd3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>OpenFlags</type>
      <name>access</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ac5b343d4b368857ad796f18794dd432c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_create</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a6d5e9e5e59a6486b223a8e52fff43108</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_exclusive</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>aabd19bd164a43109f21e300443a8e651</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_truncate</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a9917cd51c2a1d4db4d18892abe92b9ff</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_append</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a1225ecff23511c050cea4c6778bb68fa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_non_blocking</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a0a75b134342d2b8c45d8ab4007e1c88b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_read_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a962bd758cad028bb7359253d1d2cf494</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_write_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a1e14f3cedc2c0e1c6ebfdc2f68b8c169</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_read_write</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a09f0354abc63c5c2ec445f427e53ced0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_create</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a8e5a08935b7921fde6a780bd93435d05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_truncate</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a0ccdbbc19cd9bcdcbbafe7b29391bb66</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_append</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a2cdaee03788a3ca499bfa8a0f564edf8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_exclusive</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ab52df834f18a59e38d018775997f0902</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode &amp;</type>
      <name>set_non_blocking</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ae85ba95f72aef4a8165fee83b2098afd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenFlags</type>
      <name>o_flags</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>acc48a25622a68dfce0a2b8516b1e8326</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>create</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a81f16fb3e8c4b1cbdedca3ab6a6ed9e4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>create_append_write_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a73e1dd025413a261f6bc9d89425be5ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>create_truncate</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>adbb79ac5a0bda592b9ef8b0abf76bd48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>append</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>ad1475da7eba5443e6d61e8488a475344</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>append_read_write</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a5d2739a09f04b1ea2e3d97793266b8a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>read_write</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a200f68e6902aa665179255291a303111</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>read_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a751d3dd39d9f50ff529c8a955bb7b6be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>write_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>acba431eb4041c71ede2c5dc54eff7282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OpenMode</type>
      <name>append_write_only</name>
      <anchorfile>classfs_1_1_open_mode.html</anchorfile>
      <anchor>a6fe40a6eb18bb8f1f1ced0f3be8ca0ac</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::Path</name>
    <filename>classfs_1_1_path.html</filename>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>suffix</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>adc3880fb96328d93ac87d693a3410f13</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>name</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>a04e26c1a972c3606e5c2ab1c364819e9</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>parent_directory</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>ab325c681ba73b9c2cd3b07588dd472d1</anchor>
      <arglist>(var::StringView path, size_t depth=1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>base_name</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>a62db066e34eddd469d0aef1ce4d89059</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>no_suffix</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>a70947c9612c68f7cdae6c0706cfe4b88</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_hidden</name>
      <anchorfile>classfs_1_1_path.html</anchorfile>
      <anchor>a0c265fdd0c5bdc14fdbbd54da1c5bc02</anchor>
      <arglist>(var::StringView path)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::Permissions</name>
    <filename>classfs_1_1_permissions.html</filename>
    <base>fs::FileInfoFlags</base>
    <member kind="function">
      <type></type>
      <name>Permissions</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>af6b57545676267469286b675760802c1</anchor>
      <arglist>(int mode=0666)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_owner_read</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>aba067f24efa74d991ddc8e8a64d60ffa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_owner_write</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a2d0d5abc3015962f0548f85f378136ab</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_owner_execute</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>aff126c84211474772c62bcd908920fbe</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_public_read</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a4b27827132f6e68ba7db514888bc258e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_public_write</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a7ca6b698486b046fcfd60916a3baccbe</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_public_execute</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>aaffc78a7edb3702040c9e9afa81d880d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_owner_read</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a832e18b124564cedc97799b942072fdb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_owner_write</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a753833a66d3a450ebef1509ad84d7761</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_owner_execute</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>abc9cf990d6cb650144cd170e1df80ac4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_public_read</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>ae44ffc5dfcb3333abe89ccba77e0db79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_public_write</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a06757f9cb5fca653b88054266ab02335</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Permissions &amp;</type>
      <name>set_public_execute</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a9a3f57a5ecfe1a85cf1ee56933d2e281</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a58b253a86354a51c25f2893c53432bda</anchor>
      <arglist>(const Permissions &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>permissions</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a6eb4dfaba72ad500d11b47279477ebf2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Permissions</type>
      <name>all_access</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a54dfb14266dde142da127d0b9aa605d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Permissions</type>
      <name>read_only</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a33bba43f81e865ad7ea80a05c7c62755</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Permissions</type>
      <name>write_only</name>
      <anchorfile>classfs_1_1_permissions.html</anchorfile>
      <anchor>a69c3ddf5e27f055f8c537a655a3b9a7a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fs::ViewFile</name>
    <filename>classfs_1_1_view_file.html</filename>
    <base>FileAccess&lt; ViewFile &gt;</base>
    <member kind="function">
      <type></type>
      <name>ViewFile</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>a579aa41feea370cd97ff1a099771e85a</anchor>
      <arglist>(ViewFile &amp;&amp;view_file)=default</arglist>
    </member>
    <member kind="function">
      <type>ViewFile &amp;</type>
      <name>operator=</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>a314c32341f2847af6cb97cb3750773a0</anchor>
      <arglist>(ViewFile &amp;&amp;view_file)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ViewFile</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>ac5e1fcfb3df03ebaeedae32b18d1f529</anchor>
      <arglist>(var::View view)</arglist>
    </member>
    <member kind="function">
      <type>ViewFile &amp;</type>
      <name>set_flags</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>aa7c4386f5060cc50f9e7cf1eb1af0022</anchor>
      <arglist>(const OpenMode &amp;open_flags)</arglist>
    </member>
    <member kind="function">
      <type>const OpenMode &amp;</type>
      <name>flags</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>a761411b514da82006652648e69749deb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const var::View &amp;</type>
      <name>item</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>a1438ac3cadca1325ca3aa38ace3dabad</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::View &amp;</type>
      <name>item</name>
      <anchorfile>classfs_1_1_view_file.html</anchorfile>
      <anchor>a527f732ae2ed1023a7da5ba3c99c07da</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::JsonPrinter</name>
    <filename>classprinter_1_1_json_printer.html</filename>
    <base>printer::Printer</base>
    <member kind="function">
      <type></type>
      <name>JsonPrinter</name>
      <anchorfile>classprinter_1_1_json_printer.html</anchorfile>
      <anchor>ab7edc0b42319d9bd407aaf3a12ab31ca</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter</name>
    <filename>classprinter_1_1_markdown_printer.html</filename>
    <base>printer::Printer</base>
    <class kind="class">printer::MarkdownPrinter::BlockQuote</class>
    <class kind="class">printer::MarkdownPrinter::Code</class>
    <class kind="class">printer::MarkdownPrinter::Header</class>
    <class kind="class">printer::MarkdownPrinter::List</class>
    <class kind="class">printer::MarkdownPrinter::Paragraph</class>
    <class kind="class">printer::MarkdownPrinter::PrettyTable</class>
    <member kind="enumeration">
      <type></type>
      <name>Directive</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a9471c9dbc10fc91ba0d335eed68d35c8</anchor>
      <arglist></arglist>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8af534c841f49866adee307608d55c3853">no_directive</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8a1996b00b86183c4e54103ac5b8a7ea0a">emphasis_bold</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8ab449eb187bdd62b689a2dc66c4aaefaa">emphasis_italic</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8a4b9244d01dafc607c0c38788006df976">emphasis_underline</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8a592c33bcc1d195f9f0cb1097e4f1337b">emphasis_strikethrough</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8a111606e787b3daaf9700be0a7eda4410">suppress_newline</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a9471c9dbc10fc91ba0d335eed68d35c8a8231f6890fa1c3c393d8718d8b5825d4">insert_newline</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ListType</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a1193073d5af2b4dbcd7abe8a9aa8dae5</anchor>
      <arglist></arglist>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a1193073d5af2b4dbcd7abe8a9aa8dae5a2e3a2fe1ab6a59f682eec190c2b1fe27">unordered</enumvalue>
      <enumvalue file="classprinter_1_1_markdown_printer.html" anchor="a1193073d5af2b4dbcd7abe8a9aa8dae5ac934e7c6da08a36804ba7339c23644b5">ordered</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>MarkdownPrinter</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a643aad9b54821d6790eb4b5c3541ca29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ae96244d3b4f5878026eb7b834fd65114</anchor>
      <arglist>(Directive directive)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>horizontal_line</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a8822fcc1dce7c6139c4e4fc40da4c4c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_object</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a027f3a47cca23361d9cfa6190845c08d</anchor>
      <arglist>(const var::StringView key, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_object</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>add49f11cd8c3720118bc4a81472166d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a79739aa43ac34fc40259931e0cb5ca9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_array</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a531c02bec7650fde48c86113f113bf5e</anchor>
      <arglist>(const var::StringView key, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_array</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a393a0c6395de5d9127c77a281a0226e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_header</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ade82cb10e161bf81f8afb5af3586b068</anchor>
      <arglist>(const var::StringView key, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_header</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>abd1c2dd860203df94f6e7c36e776c217</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_paragraph</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a03e6f9ed3423d98ec0d239b65d143790</anchor>
      <arglist>(Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_paragraph</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ae5c913bccf4beef02527a995eaa35c69</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_list</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a0ad73a083e7c84a69e77b9b4e5bb4281</anchor>
      <arglist>(ListType type=ListType::unordered, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_list</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a1493e14c169930064de6e6bd9b047f12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_code</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a4a1dfe7a001b48f996307f67fa8aa03b</anchor>
      <arglist>(var::StringView language=&quot;&quot;, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_code</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>af72c6bf6ee1746e368ae97073723dba6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_blockquote</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>abc67e29d557fe29c6c25bbc8fd7913e2</anchor>
      <arglist>(Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_blockquote</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a07a871d667ce9b0efed46ff251c9b224</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_table</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>aa627aef52faecf12762f296e5ddefe3c</anchor>
      <arglist>(const var::StringList &amp;header, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>append_table_row</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a2744da7b80d9e0223d5caee56ccf0ad1</anchor>
      <arglist>(const var::StringList &amp;row)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_table</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a59f1a846133f27ddf5222484e864cfa6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>open_pretty_table</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a5570bf8fc27ff69f7bcf05dd2b29f75e</anchor>
      <arglist>(const var::StringList &amp;header)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>append_pretty_table_row</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>aed0bcf5906f9fbd4fd6b98d6dcc54b68</anchor>
      <arglist>(const var::StringList &amp;row)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>close_pretty_table</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ac8ac59d9bf795fe527a2e9074f567c1a</anchor>
      <arglist>(Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_pretty_table_valid</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a63933ae566637aa2258462b1d494180b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const var::Vector&lt; var::Vector&lt; var::String &gt; &gt; &amp;</type>
      <name>pretty_table</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>abb6a41550fb363291c4b097818a69aab</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>hyperlink</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a2962d3a43726246838010b8b929b0273</anchor>
      <arglist>(var::StringView text, var::StringView link)</arglist>
    </member>
    <member kind="function">
      <type>MarkdownPrinter &amp;</type>
      <name>image</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a7ef0c5235aca69db3369ca9d34bdd532</anchor>
      <arglist>(var::StringView text, var::StringView link)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ae8ca7074424d34befad40b436cc1e724</anchor>
      <arglist>(s32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ab521ff0d8c73a28250c8f947b56fd15f</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>afe61918bb5aa5fdcc0625473b682c468</anchor>
      <arglist>(s16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>ab2bf12bf763bc0f14f09e57c397e082d</anchor>
      <arglist>(u16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>acaded67c204b32d9ebc2378f40019806</anchor>
      <arglist>(s8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a8ecb06b9104152001a410167323a5605</anchor>
      <arglist>(u8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>aead81564c0e3ef87b0d654492462c1d2</anchor>
      <arglist>(float a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a644a4825dd7d757eaf65fbcfdf21ce00</anchor>
      <arglist>(void *a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>af614ec17d0d8b05080733eb00e1e58cd</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>af52a96f110a38d74e1457daf3009af36</anchor>
      <arglist>(var::View a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>af90071e21dc137df82a0dd781d3831e4</anchor>
      <arglist>(const var::String &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a6b95fbe7cf990bb667c9e24137d2cefe</anchor>
      <arglist>(const var::StringList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a7d32dbfe47a252e90656adecd01c79c0</anchor>
      <arglist>(const var::StringViewList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a87c3610e417d243f100fc853575241cb</anchor>
      <arglist>(const api::Error &amp;error_context)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_markdown_printer.html</anchorfile>
      <anchor>a13f82eb2a5084eed331ff411ccb91924</anchor>
      <arglist>(const var::DataInfo &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::BlockQuote</name>
    <filename>classprinter_1_1_markdown_printer_1_1_block_quote.html</filename>
    <member kind="function">
      <type></type>
      <name>BlockQuote</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_block_quote.html</anchorfile>
      <anchor>a13e378f45b88f89d4e7e202e4e116066</anchor>
      <arglist>(MarkdownPrinter &amp;printer, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BlockQuote</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_block_quote.html</anchorfile>
      <anchor>a14624a410005430d41a5060e277748b9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::Code</name>
    <filename>classprinter_1_1_markdown_printer_1_1_code.html</filename>
    <member kind="function">
      <type></type>
      <name>Code</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_code.html</anchorfile>
      <anchor>a03a6bea056db82dec84590494bbc57c3</anchor>
      <arglist>(MarkdownPrinter &amp;printer, var::StringView language, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Code</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_code.html</anchorfile>
      <anchor>ab91c92fc38e8635f8ee6513a9e88c6a2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::Header</name>
    <filename>classprinter_1_1_markdown_printer_1_1_header.html</filename>
    <member kind="function">
      <type></type>
      <name>Header</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_header.html</anchorfile>
      <anchor>a247d6e3d3a1b19e4b74a88a0cbbff20a</anchor>
      <arglist>(MarkdownPrinter &amp;printer, var::StringView header, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Header</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_header.html</anchorfile>
      <anchor>a9fdbaa062718403093af8c58a16e1330</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::List</name>
    <filename>classprinter_1_1_markdown_printer_1_1_list.html</filename>
    <member kind="function">
      <type></type>
      <name>List</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_list.html</anchorfile>
      <anchor>a2b8127a104bf802cc7ee1ed61ca626de</anchor>
      <arglist>(MarkdownPrinter &amp;printer, ListType type, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~List</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_list.html</anchorfile>
      <anchor>a7f42a84e01a639742c955e3f200457e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::Paragraph</name>
    <filename>classprinter_1_1_markdown_printer_1_1_paragraph.html</filename>
    <member kind="function">
      <type></type>
      <name>Paragraph</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_paragraph.html</anchorfile>
      <anchor>a858d6cfd25facd792afdc8e0561d5554</anchor>
      <arglist>(MarkdownPrinter &amp;printer, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Paragraph</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_paragraph.html</anchorfile>
      <anchor>a8e644a693625be0af3b4fbc012ed9b23</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::MarkdownPrinter::PrettyTable</name>
    <filename>classprinter_1_1_markdown_printer_1_1_pretty_table.html</filename>
    <member kind="function">
      <type></type>
      <name>PrettyTable</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_pretty_table.html</anchorfile>
      <anchor>a53e4ac2912a0167fc5bba036f630028c</anchor>
      <arglist>(MarkdownPrinter &amp;printer, const var::StringList &amp;header, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PrettyTable</name>
      <anchorfile>classprinter_1_1_markdown_printer_1_1_pretty_table.html</anchorfile>
      <anchor>a10fadb5b6837c9cd5d4aa8e9578b9219</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::NullPrinter</name>
    <filename>classprinter_1_1_null_printer.html</filename>
    <base>printer::Printer</base>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>print</name>
      <anchorfile>classprinter_1_1_null_printer.html</anchorfile>
      <anchor>a37b466a633130280ded9f6627d549ef3</anchor>
      <arglist>(const char *key, const char *value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer</name>
    <filename>classprinter_1_1_printer.html</filename>
    <base>api::ExecutionContext</base>
    <base>printer::PrinterFlags</base>
    <class kind="class">printer::Printer::Array</class>
    <class kind="class">printer::Printer::ContainerAccess</class>
    <class kind="class">printer::Printer::FlagScope</class>
    <class kind="class">printer::Printer::LevelScope</class>
    <class kind="class">printer::Printer::Object</class>
    <member kind="enumeration">
      <type></type>
      <name>IsNewline</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a645180927c5f9c0187ee7f62797dcee9</anchor>
      <arglist></arglist>
      <enumvalue file="classprinter_1_1_printer.html" anchor="a645180927c5f9c0187ee7f62797dcee9a7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classprinter_1_1_printer.html" anchor="a645180927c5f9c0187ee7f62797dcee9aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="typedef">
      <type>FlagScope</type>
      <name>FlagGuard</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a6794af9b1268003c6bacb95c576d0ef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LevelScope</type>
      <name>LevelGuard</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a4aa2c1781a670addfa7a0e2fec9f0533</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Printer</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a4fb87d0c4d818902da36b33f99b6a485</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Printer</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a8c69684486638b55c0522834e9e701bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_format_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a730a6af145675f41be6421ff5dccb672</anchor>
      <arglist>(u32 code)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_format_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a6ecfa9998d077638c7ed5811badf0949</anchor>
      <arglist>(u32 code)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_format_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a85a7b8ffd515cedc14a525ea2b9337f7</anchor>
      <arglist>(FormatType code)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_format_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a55df3f44b8276495a002304a451b9f82</anchor>
      <arglist>(FormatType code)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_color_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>af9837defdcb8b29f0b5b65ad162c05a7</anchor>
      <arglist>(u32 code)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_color_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a821f0a3f20c56190883c85cf80fe3bf3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_color_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>abbd4cd566dc6b661d76cac82ae90c6bb</anchor>
      <arglist>(ColorCode code)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ae8ca7074424d34befad40b436cc1e724</anchor>
      <arglist>(s32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ab521ff0d8c73a28250c8f947b56fd15f</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>afe61918bb5aa5fdcc0625473b682c468</anchor>
      <arglist>(s16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ab2bf12bf763bc0f14f09e57c397e082d</anchor>
      <arglist>(u16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>acaded67c204b32d9ebc2378f40019806</anchor>
      <arglist>(s8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a8ecb06b9104152001a410167323a5605</anchor>
      <arglist>(u8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>aead81564c0e3ef87b0d654492462c1d2</anchor>
      <arglist>(float a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a644a4825dd7d757eaf65fbcfdf21ce00</anchor>
      <arglist>(void *a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>af614ec17d0d8b05080733eb00e1e58cd</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>af52a96f110a38d74e1457daf3009af36</anchor>
      <arglist>(var::View a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>af90071e21dc137df82a0dd781d3831e4</anchor>
      <arglist>(const var::String &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a6b95fbe7cf990bb667c9e24137d2cefe</anchor>
      <arglist>(const var::StringList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a7d32dbfe47a252e90656adecd01c79c0</anchor>
      <arglist>(const var::StringViewList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a87c3610e417d243f100fc853575241cb</anchor>
      <arglist>(const api::Error &amp;error_context)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a13f82eb2a5084eed331ff411ccb91924</anchor>
      <arglist>(const var::DataInfo &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_verbose_level</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a7b8b03a118fa9ed613c6f756eb3f2bd4</anchor>
      <arglist>(Level level)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_verbose_level</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a6c730298caef57374c9e406c386eb650</anchor>
      <arglist>(var::StringView level)</arglist>
    </member>
    <member kind="function">
      <type>Level</type>
      <name>verbose_level</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>afd00702412a4397fea19a7533772501e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>trace</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>acf5cb38156a7d1a38756ee31e4e2dd74</anchor>
      <arglist>(const char *function, int line, var::StringView message)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>debug</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a2e234c0ab3e443c5b468f3edbac4f615</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>message</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a3124cc06ddd6301b88e4c5b6a5e41ad3</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>info</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ab108c7894118836b26914f19d165585d</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>warning</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ae1ac21257e02f9e73ddad2d9919407bf</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>error</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>af58fa658833ffc4504842356e82dea60</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>fatal</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ae47c77e600470dc81bb335424a0597f2</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>newline</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a9749a0efebd453a22731c502b54e67c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>error</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>afbbec1c5ad59f43cc984317d9da494c9</anchor>
      <arglist>(api::PrivateExecutionContext result, u32 line_number)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>enable_flags</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a94b1db13551a54d40ecfd864ff913139</anchor>
      <arglist>(Flags value)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>disable_flags</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a4705e9660b890fe0516b8ed2cf857321</anchor>
      <arglist>(Flags value)</arglist>
    </member>
    <member kind="function">
      <type>Flags</type>
      <name>flags</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ae5b2fc1b0569a3dd165f72083229d5db</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_flags</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>abfbe04bd833d9a9527d6622d34af13d7</anchor>
      <arglist>(Flags value)</arglist>
    </member>
    <member kind="function">
      <type>const api::ProgressCallback *</type>
      <name>progress_callback</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>aa201a118ad355398f0622873643e27e5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>update_progress</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a4c0919a788f00dae7e5064f160f998dc</anchor>
      <arglist>(int progress, int total)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_progress_key</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a5363fab3913492a129821270df01d734</anchor>
      <arglist>(var::StringView progress_key)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_indent_size</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a787b50d547dae7ad353558f344211dc3</anchor>
      <arglist>(u16 value)</arglist>
    </member>
    <member kind="function">
      <type>u16</type>
      <name>indent_size</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>acfbbbfd93487986e77fb4800a5290f84</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>set_progress_width</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ae47c280740f828b7fb48081a817bc046</anchor>
      <arglist>(u16 value)</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>progress_key</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a321fd30fb725303a10590f43be96d46c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Flags</type>
      <name>o_flags</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a10b36cd8f80e30197ba4f81bb07f72fb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>key_bool</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ad8a7e662b966f7ac1b7fd7782b4cbf8e</anchor>
      <arglist>(var::StringView key, bool value)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>key</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>aa867d093aaae14e638494778a5b24de7</anchor>
      <arglist>(var::StringView key, var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>key</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a08632c11c0e1c900a9aebc279ac58d0e</anchor>
      <arglist>(var::StringView key, const var::String &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>object</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>aa1221c600660b8ff0151064e233718cc</anchor>
      <arglist>(var::StringView key, const T &amp;value, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>array</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a4bf8c77b443d0ca34b43b4c92e84a361</anchor>
      <arglist>(const var::StringView key, const T &amp;value, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>open_object</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a959c25c3c569cc100787ba8a236ebb3c</anchor>
      <arglist>(var::StringView key, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>close_object</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a6ac4fbebbe0a02cc1b1f9d63d9e5b31b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>open_array</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ada37e51eb14f9541a189b27155753e0b</anchor>
      <arglist>(var::StringView key, Level level=Level::fatal)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>close_array</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a93dd732c80b78fe8fe17cf5e132aab97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>terminal_color_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a5845da8e40fb25ec17adc0eb29c28420</anchor>
      <arglist>(ColorCode code)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_open_object</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a81fdfcf02fea881c672e96340c414be6</anchor>
      <arglist>(Level verbose_level, var::StringView key)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_close_object</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ac467e16b4a8fdd5e17e79e138b902f3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_open_array</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a8c64d262c40bb8d762cbb8bf3d12c632</anchor>
      <arglist>(Level verbose_level, var::StringView key)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print_close_array</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a8b1c0864bcb98826f8ae87818ca705a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a962407a90d9dceec0799af35caef1dfd</anchor>
      <arglist>(Level level, var::StringView key, var::StringView value, IsNewline is_newline)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorCode</type>
      <name>color_code</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a66221e3b837ca4797c304a708883ca1b</anchor>
      <arglist>(var::StringView color)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>update_progress_callback</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>ac48c9fec3546c54cce9594cb38722292</anchor>
      <arglist>(void *context, int progress, int total)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char</type>
      <name>get_bitmap_pixel_character</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a2ff7ff47bc3fcd08fcf93ad472cff11b</anchor>
      <arglist>(u32 color, u8 bits_per_pixel)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static u32</type>
      <name>get_bitmap_pixel_color</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a26f7057827b3f4ab34b81b43c246fd13</anchor>
      <arglist>(char c, u8 bits_per_pixel)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>interface_print_final</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>a95bc440379e877c0c5b85a62139231cf</anchor>
      <arglist>(var::StringView view)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>write_fileno</name>
      <anchorfile>classprinter_1_1_printer.html</anchorfile>
      <anchor>aed532677dc74f5f7b2156b4d26076276</anchor>
      <arglist>(int fd, var::StringView view) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer::Array</name>
    <filename>classprinter_1_1_printer_1_1_array.html</filename>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classprinter_1_1_printer_1_1_array.html</anchorfile>
      <anchor>a89df1642633480f1c7eb20d92b08596c</anchor>
      <arglist>(Printer &amp;printer, var::StringView name, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Array</name>
      <anchorfile>classprinter_1_1_printer_1_1_array.html</anchorfile>
      <anchor>a7dad2b88d62f6a74f96ca77a2cd265b9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer::ContainerAccess</name>
    <filename>classprinter_1_1_printer_1_1_container_access.html</filename>
    <templarg>typename T</templarg>
    <member kind="function">
      <type></type>
      <name>ContainerAccess</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>a7ff92b3682bb141316caf0634f294cbe</anchor>
      <arglist>(Level verbose_level, T type)</arglist>
    </member>
    <member kind="function">
      <type>Level</type>
      <name>verbose_level</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>acba99a9d7ca97256a0df6aa4e1d13a68</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_verbose_level</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>ae87be450e7e608c045d7a47a5bdd0a9b</anchor>
      <arglist>(Level level)</arglist>
    </member>
    <member kind="function">
      <type>const u32 &amp;</type>
      <name>count</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>abda4551405c78d24640226af777d210b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32 &amp;</type>
      <name>count</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>adf5b0ac8f6f9d12f0b1210bff1d5430b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>type</name>
      <anchorfile>classprinter_1_1_printer_1_1_container_access.html</anchorfile>
      <anchor>aeab28a60d5244e7072108f98f1f145d8</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer::FlagScope</name>
    <filename>classprinter_1_1_printer_1_1_flag_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>FlagScope</name>
      <anchorfile>classprinter_1_1_printer_1_1_flag_scope.html</anchorfile>
      <anchor>a7d4e40417b4618180c523b4229211e8d</anchor>
      <arglist>(Printer &amp;printer)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FlagScope</name>
      <anchorfile>classprinter_1_1_printer_1_1_flag_scope.html</anchorfile>
      <anchor>a419d4ab041b1356fb9c8da87b7e86291</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer::LevelScope</name>
    <filename>classprinter_1_1_printer_1_1_level_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>LevelScope</name>
      <anchorfile>classprinter_1_1_printer_1_1_level_scope.html</anchorfile>
      <anchor>a18ceaa143096d8349dd5c41334cb7571</anchor>
      <arglist>(Printer &amp;printer)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LevelScope</name>
      <anchorfile>classprinter_1_1_printer_1_1_level_scope.html</anchorfile>
      <anchor>ae8891304681c4a2b071d8dffdd61ce82</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::Printer::Object</name>
    <filename>classprinter_1_1_printer_1_1_object.html</filename>
    <member kind="function">
      <type></type>
      <name>Object</name>
      <anchorfile>classprinter_1_1_printer_1_1_object.html</anchorfile>
      <anchor>a41bda03c68285e661fe2144ecc98f4af</anchor>
      <arglist>(Printer &amp;printer, var::StringView name, Level level=Level::info)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Object</name>
      <anchorfile>classprinter_1_1_printer_1_1_object.html</anchorfile>
      <anchor>aef33b212dca7e1376764084554ab54aa</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>printer::PrinterFlags</name>
    <filename>structprinter_1_1_printer_flags.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Flags</name>
      <anchorfile>structprinter_1_1_printer_flags.html</anchorfile>
      <anchor>ab7e8a8d6665b23258dde809521a66093</anchor>
      <arglist></arglist>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093ab8d1b43eae73587ba56baef574709ecb">hex</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a3f3e0fb9d945f54beaab2c0b4dd8f12a">type_unsigned</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a9ed978263150b937e941f377cade9306">type_signed</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a56f02a91b633c48cd45392fc53fa1831">type_char</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a543f7865b393f484d18069d92f17a71c">type_float</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a48a316cdc7045404083a63a6b8e9f91c">width_8</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a1a3c3593787138217681fbf5d3740b57">width_16</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a4b2dfc24fa2bc430b1e6d64d013f65f0">width_32</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a64dcce7ed1a0cfc02d4d05ab5b091c19">simple_progress</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a77ef17275947c7822a3faaf6e4526160">bold_keys</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a8a89a49a379035cfae8d3202fde4691f">bold_values</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a140e9217df91038466506008a7085cd6">bold_objects</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a7571b15bcd3d4b24155c8458b323a77c">bold_arrays</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a14663c9653d407c5a6c0a2fe385edb69">green_values</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a47bfe65a006873d3c7a2951f8f5a1175">red_values</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093aee020e1ae3b654ff0b9f723f6b1911aa">yellow_values</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093adf43741516d13941a63ed3b7283e14cd">red_errors</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a9d18221c30dd25922c8c0f23f4141e7f">yellow_warnings</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093abc0af2b1b46cc0dd82d81c6df9e9226f">cyan_keys</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a07344137fd9aa25cfa37b6af0d3fe011">yellow_keys</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a50d62cd0854d4b12ce7e5912792b8a58">magenta_keys</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093aee26908bf9629eeb4b37dac350f4754a">blob</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a51818d395b7c13ab94bd387939ac866b">cyan_values</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a04a77b89a53825f4162fbdcb200a87c7">red_keys</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093ae97579b7254c2ae47df6feee1b0b0f59">no_progress_newline</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093adc18383683777b7cf8818c177b1d4bc8">key_quotes</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ab7e8a8d6665b23258dde809521a66093a91014b3528830aee5d53e2e152ea85ad">value_quotes</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>FormatType</name>
      <anchorfile>structprinter_1_1_printer_flags.html</anchorfile>
      <anchor>a2d4d5adc15ba5bd9b2bc1b256b03a1c6</anchor>
      <arglist></arglist>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6afea087517c26fadd409bd4b9dc642555">normal</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a69dcab4a73aeec2113f69b61e6263da8">bold</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a563728df0fdd90631ac1e51258e2857d">dim</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a6dc7b4483f8c2c701a48e42db552806d">underline</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a40652ee9ae143f1c1c830f01a5449ecb">blink</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a184401f335d6b8661e04dfea47b9dcd5">inverted</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="a2d4d5adc15ba5bd9b2bc1b256b03a1c6a662f707d5491e9bce8238a6c0be92190">hidden</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ColorCode</name>
      <anchorfile>structprinter_1_1_printer_flags.html</anchorfile>
      <anchor>ae850212056f0c1782f17620d0a4601a2</anchor>
      <arglist></arglist>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a334c4a4c42fdb79d7ebc3e73b517e6f8">none</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2afea087517c26fadd409bd4b9dc642555">normal</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a1ffd9e753c8054cc61456ac7fac1ac89">black</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2abda9643ac6601722a28f238714274da4">red</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a9f27410725ab8cc8854a2769c7a516b8">green</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2ad487dd0b55dfcacdd920ccbdaeafa351">yellow</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a48d6215903dff56238e52e8891380c8f">blue</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a4c2a4a7078da0ac6733464eacfd00f86">magenta</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a6411532ba4971f378391776a9db629d3">cyan</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a770e427f6a16eb64e2ece9585ba9d193">light_gray</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a49dba686026a18435dd23b5e83eb5cfd">dark_gray</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a9fec81ba3d6228b82a5bb8fe57c3da22">light_red</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2ac10bddadd1786a8a12f96ae7db5bafb8">light_green</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a743b7827c281254e45c305696344535b">light_yellow</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="ae850212056f0c1782f17620d0a4601a2a61a2783898a9df78bb27edc33f768e6e">light_blue</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Level</name>
      <anchorfile>structprinter_1_1_printer_flags.html</anchorfile>
      <anchor>af7f6dd45e0fafecc3e492fb4b687578f</anchor>
      <arglist></arglist>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578fadf6402fd9ecc60f5a2159fdf45711cd4">fatal</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578facb5e100e5a9a3e7f6d1fd97512215282">error</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578fa7b83d3f08fa392b79e3f553b585971cd">warning</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578facaf9b6b99962bf5c2264824231d7a40c">info</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578fa78e731027d8fd50ed642340b7c9a63b3">message</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578faad42f6697b035b7580e4fef93be20b4d">debug</enumvalue>
      <enumvalue file="structprinter_1_1_printer_flags.html" anchor="af7f6dd45e0fafecc3e492fb4b687578fa04a75036e9d520bb983c5ed03b8d0182">trace</enumvalue>
    </member>
  </compound>
  <compound kind="class">
    <name>printer::PrinterTermination</name>
    <filename>classprinter_1_1_printer_termination.html</filename>
  </compound>
  <compound kind="class">
    <name>printer::YamlPrinter</name>
    <filename>classprinter_1_1_yaml_printer.html</filename>
    <base>printer::Printer</base>
    <member kind="function">
      <type></type>
      <name>YamlPrinter</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>aa649e1f5badaf122f266813f9f08761f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>YamlPrinter &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>afe7680089f9417871b57c9cc1a6e0627</anchor>
      <arglist>(const PrinterTermination &amp;printer_termination)</arglist>
    </member>
    <member kind="function">
      <type>YamlPrinter &amp;</type>
      <name>set_top_verbose_level</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>afc74d1632854f66dd4876b07aa1701ea</anchor>
      <arglist>(Level level)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>ae8ca7074424d34befad40b436cc1e724</anchor>
      <arglist>(s32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>ab521ff0d8c73a28250c8f947b56fd15f</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>afe61918bb5aa5fdcc0625473b682c468</anchor>
      <arglist>(s16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>ab2bf12bf763bc0f14f09e57c397e082d</anchor>
      <arglist>(u16 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>acaded67c204b32d9ebc2378f40019806</anchor>
      <arglist>(s8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a8ecb06b9104152001a410167323a5605</anchor>
      <arglist>(u8 a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>aead81564c0e3ef87b0d654492462c1d2</anchor>
      <arglist>(float a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a644a4825dd7d757eaf65fbcfdf21ce00</anchor>
      <arglist>(void *a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>af614ec17d0d8b05080733eb00e1e58cd</anchor>
      <arglist>(var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>af52a96f110a38d74e1457daf3009af36</anchor>
      <arglist>(var::View a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>af90071e21dc137df82a0dd781d3831e4</anchor>
      <arglist>(const var::String &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a6b95fbe7cf990bb667c9e24137d2cefe</anchor>
      <arglist>(const var::StringList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a7d32dbfe47a252e90656adecd01c79c0</anchor>
      <arglist>(const var::StringViewList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a87c3610e417d243f100fc853575241cb</anchor>
      <arglist>(const api::Error &amp;error_context)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a13f82eb2a5084eed331ff411ccb91924</anchor>
      <arglist>(const var::DataInfo &amp;a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static PrinterTermination</type>
      <name>close</name>
      <anchorfile>classprinter_1_1_yaml_printer.html</anchorfile>
      <anchor>a23ca78f0b20651cee981cd601a01bca5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sys::Cli</name>
    <filename>classsys_1_1_cli.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">sys::Cli::HandleVersion</class>
    <class kind="class">sys::Cli::ShowHelp</class>
    <member kind="function">
      <type></type>
      <name>Cli</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>acb988df1e7488723054a68170413b21a</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>const Cli &amp;</type>
      <name>handle_version</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>ae1821d45318ad985df761104f62e096f</anchor>
      <arglist>(const HandleVersion &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>const Cli &amp;</type>
      <name>operator()</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a05fe0d38ea8ac03238ebbb1bb0f01113</anchor>
      <arglist>(const HandleVersion &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>Cli &amp;</type>
      <name>set_case_sensitive</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a2cd0d033d46a92d471daf3ed5777ac5c</anchor>
      <arglist>(bool value=true)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>app_git_hash</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a9b30ae548864ca72dfe86d4184f27bfb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::GeneralString</type>
      <name>to_general_string</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a0a302dbf0d4e5d4a724ae36209aee551</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>at</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a0d64a741482d27680eaaf3b431d2b9aa</anchor>
      <arglist>(u16 value) const</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>get_option</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>aa6e8f84367b07281c931c4651fad091c</anchor>
      <arglist>(var::StringView name, var::StringView help=var::StringView()) const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>aebcd10cc902864726549ac3eb12c15bd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>size</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a1226aba7579466a4d227b309aaca8a6f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>get_name</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a8f3d590d6ff1be94fc6f0b5da85b4586</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>get_path</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a0d8fdcfa7c07b87a8804134955a94d5e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Cli &amp;</type>
      <name>show_help</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a10f7dc9613603577712d2be8a6c89aab</anchor>
      <arglist>(const ShowHelp &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>const Cli &amp;</type>
      <name>show_version</name>
      <anchorfile>classsys_1_1_cli.html</anchorfile>
      <anchor>a7c3c4845f6499ffc9a683a3cb8db2072</anchor>
      <arglist>(const ShowHelp &amp;options) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sys::Cli::HandleVersion</name>
    <filename>classsys_1_1_cli_1_1_handle_version.html</filename>
  </compound>
  <compound kind="class">
    <name>sys::Cli::ShowHelp</name>
    <filename>classsys_1_1_cli_1_1_show_help.html</filename>
  </compound>
  <compound kind="class">
    <name>sys::System</name>
    <filename>classsys_1_1_system.html</filename>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>operating_system_name</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a6c5225b8ac6591b157c5d9029c3bfb32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>processor</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a35b6f7e586a07c2e7f40633a38c162b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_processor_i386</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>af9777f8bd33914191f05715815ba70bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_processor_x86_64</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a7cb13ab91fcd040567ab9b24d23d04ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_processor_arm32</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a2d9da365ca3b480eb18dd8ab473353dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_processor_arm64</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a1ac27d7b7917f80f49525d602d0c7f30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_windows</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a725ef8649b4b8d5438c6c5c46407b1b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_macosx</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>afa0058726531272d4d7e12c5c4ed379f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_linux</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>ae776a7573e2922b0d7a5f76271686e4b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>is_stratify_os</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>ae4b89d8039c884bdb1e59d708bf0e129</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static var::StringView</type>
      <name>user_data_path</name>
      <anchorfile>classsys_1_1_system.html</anchorfile>
      <anchor>a8888092ffb6de30b40a3835ed2930374</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sys::TemporaryDirectory</name>
    <filename>classsys_1_1_temporary_directory.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type></type>
      <name>TemporaryDirectory</name>
      <anchorfile>classsys_1_1_temporary_directory.html</anchorfile>
      <anchor>a13cb2c100e9b91b25f09f8cb70e4e90f</anchor>
      <arglist>(var::StringView parent=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TemporaryDirectory</name>
      <anchorfile>classsys_1_1_temporary_directory.html</anchorfile>
      <anchor>ab192e1d0edead73e9fae5e0ae22abfae</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sys::Version</name>
    <filename>classsys_1_1_version.html</filename>
    <member kind="function">
      <type></type>
      <name>Version</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a06e5d2de4ae40c204c235b5d1d4d83fd</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Version</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a9930623d43c4787be78b545f7d35f475</anchor>
      <arglist>(const var::StringView value)</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>to_bcd</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a5d4ef0b3120378b29484f2c7c9c1d924</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u16</type>
      <name>to_bcd16</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a426fe19eab93516f5edfb4fc00ca9eaa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a9cb612bbb579972ed11ab23c9d9061c3</anchor>
      <arglist>(const Version &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>adb4cb69f6daaa2a282d28319398b9f00</anchor>
      <arglist>(const Version &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a483b352a0702c46a10a5147b6c981bbb</anchor>
      <arglist>(const Version &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a722f284951fce718a985a278a77af71d</anchor>
      <arglist>(const Version &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a9f1d5e8029806f1b2bdedcce81838735</anchor>
      <arglist>(const Version &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>var::StringView</type>
      <name>string_view</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a83036339ca4a129c6e78cda6e6b13a59</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>cstring</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a9d81ab075f912f36f5396347d0083e8d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Version</type>
      <name>from_triple</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>aef28f304bbcfc9937839056ac84b3211</anchor>
      <arglist>(u16 major, u8 minor, u8 patch)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Version</type>
      <name>from_u16</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>afd1baf5e33a5cfaab6eb96ea39b43a5e</anchor>
      <arglist>(u16 major_minor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>compare</name>
      <anchorfile>classsys_1_1_version.html</anchorfile>
      <anchor>a1968731841cf6414abefc59cb25e9f42</anchor>
      <arglist>(const Version &amp;a, const Version &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test::Case</name>
    <filename>classtest_1_1_case.html</filename>
    <member kind="function">
      <type></type>
      <name>Case</name>
      <anchorfile>classtest_1_1_case.html</anchorfile>
      <anchor>adf132ddf33d6371a3c3d7b579936e1ad</anchor>
      <arglist>(Test *test, var::StringView name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Case</name>
      <anchorfile>classtest_1_1_case.html</anchorfile>
      <anchor>ac33684c6768a42e7dd68689d3fea0f5f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test::Function</name>
    <filename>classtest_1_1_function.html</filename>
    <templarg>typename return_type</templarg>
    <templarg>typename... args</templarg>
    <base>test::Test</base>
    <member kind="typedef">
      <type>arg::Argument&lt; int, struct FunctionExpectedErrorTag &gt;</type>
      <name>ExpectedError</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>adae3e2fe0547b172447b1563dcb6b3cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>arg::Argument&lt; return_type, struct FunctionExpectedErrorTag &gt;</type>
      <name>ExpectedReturn</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a5b2efd0730b12eb697472c2b5681e2a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a99e623f2b2b1d2b900e13602b0f5ec25</anchor>
      <arglist>(const var::String &amp;test_name, return_type(*function)(args...), Test *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Function</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a4d9eed15ec59ee33ffa365012535e746</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>return_type</type>
      <name>execute_case_with_expected_return</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a5035124a94ef84d079a9679a221dc619</anchor>
      <arglist>(const char *case_name, return_type expected_value, int expected_errno, args... arguments)</arglist>
    </member>
    <member kind="function">
      <type>return_type</type>
      <name>expect_result</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a0ae00b471fa6886d7e86c6569b736931</anchor>
      <arglist>(return_type expected_result, args... arguments)</arglist>
    </member>
    <member kind="function">
      <type>return_type</type>
      <name>execute_case_with_less_than_zero_on_error</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>a5feb97099c9ec5d794e7bb8e83f60539</anchor>
      <arglist>(const char *case_name, int expected_errno, args... arguments)</arglist>
    </member>
    <member kind="function">
      <type>return_type</type>
      <name>expect_error</name>
      <anchorfile>classtest_1_1_function.html</anchorfile>
      <anchor>acc83adc6728d5a6016e75abb363cc251</anchor>
      <arglist>(int expected_errno, args... arguments)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test::Test</name>
    <filename>classtest_1_1_test.html</filename>
    <base>api::ExecutionContext</base>
    <base>test::TestFlags</base>
    <class kind="class">test::Test::Initialize</class>
    <class kind="class">test::Test::Scope</class>
    <class kind="class">test::Test::TimedScope</class>
    <member kind="function">
      <type></type>
      <name>Test</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a670fc9289ded34c09ac11883b8010eb7</anchor>
      <arglist>(var::StringView name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Test</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a328ed6bba3b51a1359639f9c2b4a5616</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>execute</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a136a3dc177b94c124169bd132e27000c</anchor>
      <arglist>(const sys::Cli &amp;cli)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>execute</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a05cf48adbda5d3590f851363c05dddf2</anchor>
      <arglist>(ExecuteFlags execute_flags=ExecuteFlags::all)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>execute_api_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>af8b2dff5d7573d91c5da5c8c7e4c7954</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>execute_performance_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a0becd1ba426a6577d76c38090b638b32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>execute_stress_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a449f154f14d1e8d4255a6f5d5484aa7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>execute_class_api_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a923274a9e149cdcd84ebf865fa5c2f63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>execute_class_performance_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a8cef321cf947ea101c0b42916f5c4e7b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>execute_class_stress_case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a5156e4d5b2dcdd80f052aa98ae578f84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>result</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>aeca4c8f92206828dbe0a032bac8dd90e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>case_result</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a6778c093cb2bb1705741adb757c30715</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_case_failed</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a3cbe9df008c48370985981f02ee6f5d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>expect</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>ab1d4eae2af931c03bb6e023eeeecbd8e</anchor>
      <arglist>(const char *function, unsigned int line, bool value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initialize</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a41b28458470c8bc057133307e5e65718</anchor>
      <arglist>(const Initialize &amp;options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>finalize</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>aff841db16eb845c2cc2b285b433538f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ExecuteFlags</type>
      <name>parse_execution_flags</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a9d647f0297c1c979e5e123ccbbafc5d5</anchor>
      <arglist>(const sys::Cli &amp;cli)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static u32</type>
      <name>parse_test</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a605699e964a0a07c66554477655467fd</anchor>
      <arglist>(const sys::Cli &amp;cli, var::StringView name, u32 test_flag)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>final_result</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a095e6c0ef3bdabd69a978d122196155a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const chrono::ClockTimer &amp;</type>
      <name>case_timer</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a97dd420741142f885cc7b56305944b18</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>chrono::ClockTimer &amp;</type>
      <name>case_timer</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a6b2510ffffc49461a724dcf9ab44f4af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>var::StringView</type>
      <name>name</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>abdc81fde13342307cfad7d7de7b651c0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static u32</type>
      <name>get_score</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a6baf4dc50b42482230dad18692e65c74</anchor>
      <arglist>(u32 microseconds)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static printer::Printer &amp;</type>
      <name>printer</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a2860d7b969353db1e64ecc14b46a84e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Case</name>
      <anchorfile>classtest_1_1_test.html</anchorfile>
      <anchor>a8162a4e0d885beccd1b1d04a69a20577</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test::Test::Initialize</name>
    <filename>classtest_1_1_test_1_1_initialize.html</filename>
  </compound>
  <compound kind="class">
    <name>test::Test::Scope</name>
    <filename>classtest_1_1_test_1_1_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>Scope</name>
      <anchorfile>classtest_1_1_test_1_1_scope.html</anchorfile>
      <anchor>a3e823a778b255e467ff83c0f08714620</anchor>
      <arglist>(const Initialize &amp;options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Scope</name>
      <anchorfile>classtest_1_1_test_1_1_scope.html</anchorfile>
      <anchor>acdc6caf1bf5c8c97b4c001f2dc540055</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>test::Test::TimedScope</name>
    <filename>classtest_1_1_test_1_1_timed_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>TimedScope</name>
      <anchorfile>classtest_1_1_test_1_1_timed_scope.html</anchorfile>
      <anchor>a6ab99418e505e54bed45c87e19bf41c0</anchor>
      <arglist>(Test &amp;test, const var::StringView name, const chrono::MicroTime &amp;minimum, const chrono::MicroTime &amp;maximum)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TimedScope</name>
      <anchorfile>classtest_1_1_test_1_1_timed_scope.html</anchorfile>
      <anchor>a13cd9e60b1a1d65ba665f46ac318cc16</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>test::TestFlags</name>
    <filename>structtest_1_1_test_flags.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ExecuteFlags</name>
      <anchorfile>structtest_1_1_test_flags.html</anchorfile>
      <anchor>a70b1ad4faa4bfbc819dd3eee28c82c41</anchor>
      <arglist></arglist>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41a8a5da52ed126447d359e70c05721a8aa">api</enumvalue>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41ae10a36f1a5231e597daf8f42dc1ab55a">stress</enumvalue>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41ac05f6c233521207f6fe311afef550c3c">performance</enumvalue>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41a73748a23bf2f77b41899e6dd3610c458">all_types</enumvalue>
      <enumvalue file="structtest_1_1_test_flags.html" anchor="a70b1ad4faa4bfbc819dd3eee28c82c41aa181a603769c1f98ad927e7367c7aa51">all</enumvalue>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Cond</name>
    <filename>classthread_1_1_cond.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Cond::Attributes</class>
    <member kind="typedef">
      <type>Mutex::ProcessShared</type>
      <name>ProcessShared</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>afb661a405c18ce6cb4ffa60055d3f8d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a0daccbb322da063c7ace68ec51a96792</anchor>
      <arglist>(Mutex &amp;mutex)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>abfcc6e650ab551a1b514cfdaa89d6ff7</anchor>
      <arglist>(Mutex &amp;mutex, const Attributes &amp;attr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a4f4e5c46f7717b4b89891bcf9adfac40</anchor>
      <arglist>(const Cond &amp;Cond)=delete</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a7fa8b1e0b9c075b9d3d81ffabff51df6</anchor>
      <arglist>(const Cond &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a6cdbd0ac7a00fe6d40f8a1df8c217de2</anchor>
      <arglist>(Cond &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>ae43cb8cb8171c22151faf3fbc1b8cd35</anchor>
      <arglist>(Cond &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Cond</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a3c51dedc44367303bf54062a2db1dfa7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>lock</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a9b26984f3efbc11c9d3d7279ca93d381</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>unlock</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>abd66bb78900809eba3e067d142056407</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>wait</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>aae78d0702979c3cff408c13ccbda120a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>wait_timed</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>abb19bdffc64d72d3154bdef804dc4295</anchor>
      <arglist>(const chrono::ClockTime &amp;timeout)</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>signal</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>ac00ce7edd5617f955451287d0070cc3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>broadcast</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a0fe3dcb47ec3ee3c9fb0a675f26e6d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Cond &amp;</type>
      <name>wait_until_asserted</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a36293e1e88c10ebab4b500c1eab58a93</anchor>
      <arglist>(const chrono::ClockTime &amp;timeout=chrono::ClockTime())</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>mutex</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>a48830894e5a5d730ffdeb22b43f80300</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Mutex &amp;</type>
      <name>mutex</name>
      <anchorfile>classthread_1_1_cond.html</anchorfile>
      <anchor>ae544755a44f866c20276e98eea8fcc82</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Cond::Attributes</name>
    <filename>classthread_1_1_cond_1_1_attributes.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type></type>
      <name>Attributes</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>afe836293984f8ddd71e0aa7ebcd943d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Attributes</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>aa35c345e76264c03faddedd78a413948</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_pshared</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>a99f8ea4a468b838bf65e17874cc38324</anchor>
      <arglist>(bool value=true)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_pshared</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>a45da6b2e79e737dfbe8fe9bb430af4dd</anchor>
      <arglist>(ProcessShared pshared)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_is_pshared</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>a17f47b09ee4f5815d45a0838f0023842</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ProcessShared</type>
      <name>get_pshared</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>ae8ceb624876851df3c50eb3d9bc2f9be</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_cond_1_1_attributes.html</anchorfile>
      <anchor>a7b3a3b08a18ec6e57d9a2f52744212c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mq</name>
    <filename>classthread_1_1_mq.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Mq::Attributes</class>
    <class kind="class">thread::Mq::File</class>
    <class kind="class">thread::Mq::Info</class>
    <member kind="enumeration">
      <type></type>
      <name>IsExclusive</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a138ac27c1719d6302fc9027045f2a1e7</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_mq.html" anchor="a138ac27c1719d6302fc9027045f2a1e7a7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classthread_1_1_mq.html" anchor="a138ac27c1719d6302fc9027045f2a1e7aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="typedef">
      <type>fs::OpenMode</type>
      <name>OpenMode</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>acb06e4981b9671af613138d95ee31d99</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>ab29bcdd53d965ee49af785787e8f6ca7</anchor>
      <arglist>()=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a86146937ac710e2e6a5abd70d2401cda</anchor>
      <arglist>(const Mq &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a3403f195347fe3f337e60fc7f6079d7a</anchor>
      <arglist>(const Mq &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>ad078a43564019fc2f2b1766af93defd2</anchor>
      <arglist>(Mq &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>acd5af781086c2b647f7660dd5992e73d</anchor>
      <arglist>(Mq &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a5227ca15e919cb47413e2497f290f7c4</anchor>
      <arglist>(var::StringView name, const fs::OpenMode &amp;open_mode=fs::OpenMode::read_write())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a0f2160b8f8be756f9218d2d2f8076f7a</anchor>
      <arglist>(const Attributes &amp;attributes, IsExclusive is_exclusive, var::StringView name, const OpenMode &amp;open_mode=OpenMode::read_write(), fs::Permissions perms=fs::Permissions(0666))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Mq</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a9bb4b2ad3bb14b4897459081193aaf7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>aeb4c47aec9dbc467c8a417bda6ebc6cb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Info</type>
      <name>get_info</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>ae45c8eb90a1edea50973b360f1274d32</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>set_flags</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a0ccebdd481b7755d221bd0437f76d61e</anchor>
      <arglist>(OpenMode open_mode)</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>receive</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a582e6ea306ee7ee1aff1072d11a54a69</anchor>
      <arglist>(var::View message)</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>send</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a93f6b00b014c6366e2e70accc6e4ebb1</anchor>
      <arglist>(var::View message)</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>receive_timed</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a889122e45a35d43e978315372a51df2e</anchor>
      <arglist>(var::View message, const chrono::ClockTime &amp;relative_timeout)</arglist>
    </member>
    <member kind="function">
      <type>Mq &amp;</type>
      <name>send_timed</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>a66e09b4f30b09c99404f23b61c8c7a1c</anchor>
      <arglist>(var::View message, const chrono::ClockTime &amp;relative_timeout)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>unlink</name>
      <anchorfile>classthread_1_1_mq.html</anchorfile>
      <anchor>afc5a0a8cb2a7bca304aa3d6840a9b615</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mq::Attributes</name>
    <filename>classthread_1_1_mq_1_1_attributes.html</filename>
    <member kind="function">
      <type></type>
      <name>Attributes</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>aef6abbcec8d6eba8c49b098a8a4c8765</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>flags</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a8a811faec8604fd7c517d059ef0e86d0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>current_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a2948472472cb6a6010fe495890eab9b5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>maximum_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a7b7ee6c3f39df277bbb02e5486d39447</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>message_size</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a28426c36ffa700b81496bd08019c9754</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_maximum_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a064dbfa8bcc9f556cd2a1597482ce766</anchor>
      <arglist>(long v)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>af68806128750c2cbe49c48b036ec202c</anchor>
      <arglist>(long v)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_message_size</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a1ac6a7094f87e0e6592e7c768881eb7d</anchor>
      <arglist>(long v)</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq_1_1_attributes.html</anchorfile>
      <anchor>a834acb177a845f84131939ece3a2307c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mq::File</name>
    <filename>classthread_1_1_mq_1_1_file.html</filename>
    <base>FileAccess&lt; File &gt;</base>
    <member kind="function">
      <type></type>
      <name>File</name>
      <anchorfile>classthread_1_1_mq_1_1_file.html</anchorfile>
      <anchor>a8a7b169f043e1a2664010d4c0f135897</anchor>
      <arglist>(Mq &amp;message_queue)</arglist>
    </member>
    <member kind="function">
      <type>File &amp;</type>
      <name>set_size</name>
      <anchorfile>classthread_1_1_mq_1_1_file.html</anchorfile>
      <anchor>a20bc028d8c9468fa9580dfde0a4db677</anchor>
      <arglist>(size_t size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mq::Info</name>
    <filename>classthread_1_1_mq_1_1_info.html</filename>
    <member kind="function">
      <type></type>
      <name>Info</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a421414dc77fd4cb1cefa610ea2ad18e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OpenMode::OpenFlags</type>
      <name>flags</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a895333388c619da97f5ee5c5ca1a8ec5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>o_flags</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a4b441287a424509aa6e56673cb423c93</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>current_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a7e687e1ee186d12217401b4d85c17423</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>maximum_message_count</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a2dbc25cabf1ef2eaf6311be9239af623</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>message_size</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a70238205fad91f027d7898ab609bf059</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Mq</name>
      <anchorfile>classthread_1_1_mq_1_1_info.html</anchorfile>
      <anchor>a834acb177a845f84131939ece3a2307c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mutex</name>
    <filename>classthread_1_1_mutex.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Mutex::Attributes</class>
    <class kind="class">thread::Mutex::Guard</class>
    <member kind="enumeration">
      <type></type>
      <name>Type</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a693a47bbec1de53981a35ac2271e1531</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_mutex.html" anchor="a693a47bbec1de53981a35ac2271e1531afea087517c26fadd409bd4b9dc642555">normal</enumvalue>
      <enumvalue file="classthread_1_1_mutex.html" anchor="a693a47bbec1de53981a35ac2271e1531af8e45531a3ea3d5c1247b004985175a4">recursive</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Protocol</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a8b39512d7e98c464519653bec591c8e1</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_mutex.html" anchor="a8b39512d7e98c464519653bec591c8e1ad694f924850480014e0ff999ff5f5048">priority_none</enumvalue>
      <enumvalue file="classthread_1_1_mutex.html" anchor="a8b39512d7e98c464519653bec591c8e1aa299c2ab4f3f472246fb611d979a4b0a">priority_inherit</enumvalue>
      <enumvalue file="classthread_1_1_mutex.html" anchor="a8b39512d7e98c464519653bec591c8e1a8440fcd90a18a110241bf8d84a4e5c8e">priority_protect</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ProcessShared</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>ac8f283e77dd72d383568594295b2505f</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_mutex.html" anchor="ac8f283e77dd72d383568594295b2505fa9e81e7b963c71363e2fb3eefcfecfc0e">shared</enumvalue>
      <enumvalue file="classthread_1_1_mutex.html" anchor="ac8f283e77dd72d383568594295b2505fafe98605c4fd6e7434fb6e1db37b30ef9">private_</enumvalue>
    </member>
    <member kind="typedef">
      <type>Guard</type>
      <name>Scope</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a83595b63e94a97c782bf0a60d0f72e56</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mutex</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a76957f2cf0e90bd989a4f32b39abdf70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mutex</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a1ac1b695c751a43dce5ad4a2164ce6e2</anchor>
      <arglist>(const Attributes &amp;attr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mutex</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a075d7eee7dd8a7318cd0a6ba88e90796</anchor>
      <arglist>(const Mutex &amp;mutex)=delete</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>aa46b4029f7d32839a3eb60fa64e8d405</anchor>
      <arglist>(const Mutex &amp;mutex)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Mutex</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>adc4c01da9f80a2d98dd7fc33e7bb657f</anchor>
      <arglist>(Mutex &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a5490706f5b09cc22fcf8333cba6294a8</anchor>
      <arglist>(Mutex &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Mutex</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a73e58706bc924f42dccea97f282372f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>lock</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>af11aa800b73e9dde04f2612c05b50420</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>lock_timed</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a86be63e9f5683686b331cdaec5b20318</anchor>
      <arglist>(const chrono::ClockTime &amp;clock_time)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>try_lock</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a85d5fa4de48554489a044a3bf196d6a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>unlock</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>aac010af728874f7d3209af5bf7982bdd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Mutex &amp;</type>
      <name>unlock_with_error_check</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a936bcb814216c9bf1806c87b2030bf70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Cond</name>
      <anchorfile>classthread_1_1_mutex.html</anchorfile>
      <anchor>a7b3a3b08a18ec6e57d9a2f52744212c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mutex::Attributes</name>
    <filename>classthread_1_1_mutex_1_1_attributes.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type></type>
      <name>Attributes</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>aaf59722f935d79a33e160d30bf40245f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Attributes</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a6563258d084c58fcf63f0a57f4be01c7</anchor>
      <arglist>(const pthread_mutexattr_t &amp;mutexattr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Attributes</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>abfec9898a70f24263012fc09e7b81659</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a9617096c0d7e866a95ced17742855894</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_priority_ceiling</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a6fb6678997ecf433c8ed330f14637dbb</anchor>
      <arglist>(int ceiling)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_protocol</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a786b85c0f048fa612a1a4b9b5a652903</anchor>
      <arglist>(Protocol value)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_process_shared</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a9f48eaa73366a15e9b5a2c8c0684b2a3</anchor>
      <arglist>(ProcessShared process_shared)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_type</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>aa496a9286bf31e1d353abb14f0ec0253</anchor>
      <arglist>(Type value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_priority_ceiling</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>af3f461b905defb8a193a16572b239c59</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Protocol</type>
      <name>get_protocol</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a09c9518f6f5ac303bfa624f370d2d0ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>get_type</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a8a949f2d3ab9c18e70febf0c7cf639c0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ProcessShared</type>
      <name>get_process_shared</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>ab9c2baafbcd8fc241a76a778afce7f18</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Mutex</name>
      <anchorfile>classthread_1_1_mutex_1_1_attributes.html</anchorfile>
      <anchor>a0299a51a8b97fb3200509d92ba10fa2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Mutex::Guard</name>
    <filename>classthread_1_1_mutex_1_1_guard.html</filename>
    <member kind="function">
      <type></type>
      <name>Guard</name>
      <anchorfile>classthread_1_1_mutex_1_1_guard.html</anchorfile>
      <anchor>a389a7da583549fce24fdfcdfa6a721d1</anchor>
      <arglist>(Mutex *mutex)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Guard</name>
      <anchorfile>classthread_1_1_mutex_1_1_guard.html</anchorfile>
      <anchor>a54daa64ee55e8791df161957b6ddc58a</anchor>
      <arglist>(Mutex &amp;mutex)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Guard</name>
      <anchorfile>classthread_1_1_mutex_1_1_guard.html</anchorfile>
      <anchor>a1b5c076408f0872e25883f642b1f32ec</anchor>
      <arglist>(Mutex &amp;mutex, void *context, void(*execute)(void *))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Guard</name>
      <anchorfile>classthread_1_1_mutex_1_1_guard.html</anchorfile>
      <anchor>abfa30152bee07815fa6943319b45724b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Sched</name>
    <filename>classthread_1_1_sched.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Sched::SetScheduler</class>
    <member kind="enumeration">
      <type></type>
      <name>Policy</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ae7889312e0d18a32eca5a899ac216ca7</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_sched.html" anchor="ae7889312e0d18a32eca5a899ac216ca7a4412c3395f407a75c2adce7824ebf428">round_robin</enumvalue>
      <enumvalue file="classthread_1_1_sched.html" anchor="ae7889312e0d18a32eca5a899ac216ca7acf54937a2330ac17aa523bf7130911a3">fifo</enumvalue>
      <enumvalue file="classthread_1_1_sched.html" anchor="ae7889312e0d18a32eca5a899ac216ca7a795f3202b17cb6bc3d4b771d8c6c9eaf">other</enumvalue>
    </member>
    <member kind="function">
      <type>const Sched &amp;</type>
      <name>yield</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ab1161457dad8eb17a76db3cbfcd8d347</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Sched &amp;</type>
      <name>set_scheduler</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>a0beccb54a1477c4e7107c680f3ecb1bd</anchor>
      <arglist>(const SetScheduler &amp;options) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static pid_t</type>
      <name>get_pid</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ac0c476d4b78a2311f262a1f61a0ee817</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>get_priority_max</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ae397c58615dc4aac88dee9d946478d90</anchor>
      <arglist>(Policy value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>get_priority_min</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ac47758ee74e4d5733b1651420c9f3b5e</anchor>
      <arglist>(Policy value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>get_priority</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>ad50993870e644c997de037c757841c90</anchor>
      <arglist>(pid_t pid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>get_rr_interval</name>
      <anchorfile>classthread_1_1_sched.html</anchorfile>
      <anchor>a9e3eef0c9366b38ebb13328f0a72e7eb</anchor>
      <arglist>(pid_t pid)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Sched::SetScheduler</name>
    <filename>classthread_1_1_sched_1_1_set_scheduler.html</filename>
  </compound>
  <compound kind="class">
    <name>thread::SemAccess</name>
    <filename>classthread_1_1_sem_access.html</filename>
    <templarg>class Derived</templarg>
    <base>thread::SemaphoreObject</base>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>post</name>
      <anchorfile>classthread_1_1_sem_access.html</anchorfile>
      <anchor>acbf9373d93d13488acc295327dfb4936</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>wait_timed</name>
      <anchorfile>classthread_1_1_sem_access.html</anchorfile>
      <anchor>a81f0852eb52d8bb9cfeff67c13f719f1</anchor>
      <arglist>(const chrono::ClockTime &amp;clock_time)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>timedwait</name>
      <anchorfile>classthread_1_1_sem_access.html</anchorfile>
      <anchor>a3aa50d18702a0781af7708f1a730f3fc</anchor>
      <arglist>(const chrono::ClockTime &amp;clock_time)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>try_wait</name>
      <anchorfile>classthread_1_1_sem_access.html</anchorfile>
      <anchor>adb629bc5484d73963c8cdde711eed1ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>wait</name>
      <anchorfile>classthread_1_1_sem_access.html</anchorfile>
      <anchor>a55c4d1e07e1107daff01fc100bf8b266</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Semaphore</name>
    <filename>classthread_1_1_semaphore.html</filename>
    <base>SemAccess&lt; Semaphore &gt;</base>
    <member kind="enumeration">
      <type></type>
      <name>IsExclusive</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a03dfcac8678fc554c034b5b878eab225</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_semaphore.html" anchor="a03dfcac8678fc554c034b5b878eab225a7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classthread_1_1_semaphore.html" anchor="a03dfcac8678fc554c034b5b878eab225aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>Semaphore</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a68562e931a4d806c42fd1796c1f709d8</anchor>
      <arglist>(const Semaphore &amp;value)=delete</arglist>
    </member>
    <member kind="function">
      <type>Semaphore &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a4e7cecfab93e775b172f4d513ca2329d</anchor>
      <arglist>(const Semaphore &amp;value)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Semaphore</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>ab9d7494cf387c9af3c816eab80235e56</anchor>
      <arglist>(Semaphore &amp;&amp;value) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Semaphore &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>afa004cef8d6cb73ee0ad40282eb50739</anchor>
      <arglist>(Semaphore &amp;&amp;value) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Semaphore</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a554387d23514aefa257cffddfa3162e7</anchor>
      <arglist>(var::StringView name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Semaphore</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a30f5728fa73d6ce7face709f902e2698</anchor>
      <arglist>(int value, IsExclusive is_exclusive, var::StringView name, fs::Permissions perms=fs::Permissions(0666))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Semaphore</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>aade1fe65b983e9dfc41dde9f07697198</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Semaphore &amp;</type>
      <name>unlink</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>ab3223f6526fdcaa02e042a78764d63ff</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Semaphore &amp;</type>
      <name>unlink</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a40bcd8512c176f1d14fb74c66a341c5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>unlink</name>
      <anchorfile>classthread_1_1_semaphore.html</anchorfile>
      <anchor>a5d21feddab90b035e8e175bf816a896b</anchor>
      <arglist>(var::StringView name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::SemaphoreObject</name>
    <filename>classthread_1_1_semaphore_object.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type></type>
      <name>SemaphoreObject</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a043f51a6f9539394a6dc89cf695e518b</anchor>
      <arglist>(const SemaphoreObject &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a549513eac2fe19e91d9c58aba0a17628</anchor>
      <arglist>(const SemaphoreObject &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_value</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a6b0eb84a1e32058800072bd1995f0562</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>post</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>af1e6485ccbdf15dd3318648dd7935111</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>wait_timed</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>ab29660addc1dd79af30a2aab903332d2</anchor>
      <arglist>(const chrono::ClockTime &amp;clock_time)</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>timedwait</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a81f9e5e81120b7232e792f51ee4f4d3c</anchor>
      <arglist>(const chrono::ClockTime &amp;clock_time)</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>try_wait</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a3dbf9243429c5d940927fb6e4a455363</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SemaphoreObject &amp;</type>
      <name>wait</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a684b43099c95a5fc3f034bb15806a1fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>SemaphoreObject</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a77eade447315e5ca1b9134c43c5bec4f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>SemaphoreObject</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a071102ada7a6d6228e6b781ea427121e</anchor>
      <arglist>(SemaphoreObject &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SemaphoreObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a9d1a0b7b0e47a3cf42b74c995b563bd6</anchor>
      <arglist>(SemaphoreObject &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>UnnamedSemaphore</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>a22c6b2b46e816104eacba41925d6bd5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Semaphore</name>
      <anchorfile>classthread_1_1_semaphore_object.html</anchorfile>
      <anchor>aebe70aacee812bed6d2510814cba9c8a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Signal</name>
    <filename>classthread_1_1_signal.html</filename>
    <base>thread::SignalFlags</base>
    <class kind="class">thread::Signal::Event</class>
    <class kind="class">thread::Signal::HandlerScope</class>
    <class kind="class">thread::Signal::Set</class>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a7cf550fb8d52c092ecb1ce3bfb71526e</anchor>
      <arglist>(Number signo, int signal_value=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>ae0e625ef295aa627223df9c731079f0d</anchor>
      <arglist>(Number signo, void *signal_pointer)</arglist>
    </member>
    <member kind="function">
      <type>const Signal &amp;</type>
      <name>send</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a03060ff4872ce848f70ff287b89368f0</anchor>
      <arglist>(pid_t pid) const</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>send</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>ac74a9d4ce00504ea98675221406d721f</anchor>
      <arglist>(pid_t pid)</arglist>
    </member>
    <member kind="function">
      <type>const Signal &amp;</type>
      <name>queue</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>aec9f8733c71a84047e12a38a36b37841</anchor>
      <arglist>(pid_t pid) const</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>queue</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a65485436c10f178a0cac95c5924e214c</anchor>
      <arglist>(pid_t pid)</arglist>
    </member>
    <member kind="function">
      <type>const Signal &amp;</type>
      <name>send</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a27202d8d368bf951846bc94caf4a042a</anchor>
      <arglist>(const Thread &amp;t) const</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>send</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a4bd7ed60063a42b7190320c3599af659</anchor>
      <arglist>(const Thread &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>set_handler</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>abcd64b619c98eeb7c4a9ba1c4bf1bafa</anchor>
      <arglist>(const SignalHandler &amp;handler)</arglist>
    </member>
    <member kind="function">
      <type>Signal &amp;</type>
      <name>reset_handler</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a7f5ae6c0e1b3c8fe6ee116f5fc3aa1b5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Number</type>
      <name>number</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>af941b680aaa4cf5849c226e0d6801115</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>signo</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a213f7c8abf7fa3e454158403271d13b3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>sigvalue</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a25d7de6a55f3e817b5a6784c6ef56cb5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>sigptr</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a077ca5ad277934240894e753648bdddc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Signal</type>
      <name>wait</name>
      <anchorfile>classthread_1_1_signal.html</anchorfile>
      <anchor>a988b797316b70354dc14e076821cf778</anchor>
      <arglist>(const Set &amp;set)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Signal::Event</name>
    <filename>classthread_1_1_signal_1_1_event.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Notify</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>adb94139483c6953c7bc4aaa7a00ee0c2</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_signal_1_1_event.html" anchor="adb94139483c6953c7bc4aaa7a00ee0c2a334c4a4c42fdb79d7ebc3e73b517e6f8">none</enumvalue>
      <enumvalue file="classthread_1_1_signal_1_1_event.html" anchor="adb94139483c6953c7bc4aaa7a00ee0c2a521345a9fb579f52117f27be6e0673ee">signal</enumvalue>
      <enumvalue file="classthread_1_1_signal_1_1_event.html" anchor="adb94139483c6953c7bc4aaa7a00ee0c2adc127f5d2483352fd20eaddb38feb6d2">thread</enumvalue>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_notify</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>ae1f1e8316c92e889b183d77c20220d20</anchor>
      <arglist>(Notify value)</arglist>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_number</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>a797d58f28d9853555286c81658d72fd9</anchor>
      <arglist>(Number value)</arglist>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_value</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>aa1246ee330b153ba1f2cc5ded8ce6859</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_value</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>a40bf3c1184bb33edc69f37750ef3da17</anchor>
      <arglist>(void *value)</arglist>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_notify_function</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>a9141bae4742a123f1aba884e5dc78149</anchor>
      <arglist>(void(*value)(sigval))</arglist>
    </member>
    <member kind="function">
      <type>Event &amp;</type>
      <name>set_notify_attributes</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>ad2058673346e8a4cf37b7fa69f97c764</anchor>
      <arglist>(pthread_attr_t *value)</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Timer</name>
      <anchorfile>classthread_1_1_signal_1_1_event.html</anchorfile>
      <anchor>a50de43af5bed41f30c071d8cce0e81bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Signal::HandlerScope</name>
    <filename>classthread_1_1_signal_1_1_handler_scope.html</filename>
    <member kind="function">
      <type></type>
      <name>HandlerScope</name>
      <anchorfile>classthread_1_1_signal_1_1_handler_scope.html</anchorfile>
      <anchor>a00cb809535fccefe4be695c238293997</anchor>
      <arglist>(Signal &amp;signal, const SignalHandler &amp;handler)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~HandlerScope</name>
      <anchorfile>classthread_1_1_signal_1_1_handler_scope.html</anchorfile>
      <anchor>a2d8ecb0045ed29c0e9a9866509a1d031</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Signal::Set</name>
    <filename>classthread_1_1_signal_1_1_set.html</filename>
    <member kind="function">
      <type>Set &amp;</type>
      <name>add</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>a0844b84e4befdfab5efc17a2204e9b39</anchor>
      <arglist>(Number signo)</arglist>
    </member>
    <member kind="function">
      <type>Set &amp;</type>
      <name>del</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>a2ffa3c0b88dda61212ff53bc3341cce7</anchor>
      <arglist>(Number signo)</arglist>
    </member>
    <member kind="function">
      <type>Set &amp;</type>
      <name>fill</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>a9d0f6c528eb1b28acde378232a81ae77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Set &amp;</type>
      <name>clear</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>a63d57696bdc62902fd36cf73dad83e20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_member</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>adbb0089473dff5c03b53570bd1f9a08c</anchor>
      <arglist>(Number signo) const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Signal</name>
      <anchorfile>classthread_1_1_signal_1_1_set.html</anchorfile>
      <anchor>ac5526429c5a50ac492f6e8113c59b18a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::SignalFlags</name>
    <filename>classthread_1_1_signal_flags.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="enumeration">
      <type></type>
      <name>Number</name>
      <anchorfile>classthread_1_1_signal_flags.html</anchorfile>
      <anchor>ac44be3adb1346bb8aecb2596a3cc85b7</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a5bb94a1c12413a2e5d14deabab29f2aa">abort</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7af7ec5feba07906f740ae06f34e8448ce">fpe</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a2414c252176310b2c04547257948c7b7">interrupt</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a55f99613fd4c7efa27297f0b2f04407f">illegal</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a679fe1db8dc7308e44404587d0348c5e">segmentation</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a1459e53d3fbaa95cebaf90860dd7a259">terminate</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a6486b4e98228b83d4b13d54febe5f170">alarm</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7ad20f83ee6933aa1ea047fe5cbd9c1fd5">bus</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a1b7d5726533ab525a8760351e9b5e415">child</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a5b4404524e842940120cc65b3214d40b">continue_</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a11abfa6c0027efec2d323fc275e135cc">handup</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a534735884d341071762ede7af01c53e8">kill</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a20826a3cb51d6c7d9c219c7f4bf4e5c9">pipe</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7adbd73c2b545209688ed794c0d5413d5a">quit</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7aef399b2d446bb37b7c32ad2cc1b6045b">stop</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a618403cb769145797a29df601ec30d46">terminal_stop</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7ad2a98820b9de91a392bfdb4d81315e19">terminal_input</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a0356b5d58b4d86a21eb202d5fb9ebbfa">terminal_output</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a24c9e15e52afc47c225b757e7bee1f9d">user1</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a7e58d63b60197ceb55a1c487989a3720">user2</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7aceef42ff8376b17ac66fd0bbc7a7a0be">profiling_timer</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a54b53072540eeeb8f8e9343e71f28176">system</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7aca97f68cf88e0d3b9c652c05c7619575">trap</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a1c0f66a0443282385b46fb9ad0a9e092">high_bandwidth</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7ac3c6681439c909c1d4d4fbd896113b65">virtual_alarm</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7aa6a06e93732e5408f7574578bd4dd04c">cpu_time_limit</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a130cbacc6f939c09658f7a4170d116c5">file_size_limit</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7ab0f6dfb42fa80caee6825bfecd30f094">poll</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a3c90bacea6964c272fe269bd80917fe0">realtime_min</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7a37e2a166d3ab28426a1d1a481d356d33">realtime</enumvalue>
      <enumvalue file="classthread_1_1_signal_flags.html" anchor="ac44be3adb1346bb8aecb2596a3cc85b7ae0b060bf5deaca0b6031b22ccce65323">realtime_max</enumvalue>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::SignalHandler</name>
    <filename>classthread_1_1_signal_handler.html</filename>
    <base>thread::SignalFlags</base>
    <class kind="class">thread::SignalHandler::Construct</class>
    <member kind="function">
      <type></type>
      <name>SignalHandler</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>a2e489c5566d5bf70cbe006200dafabcf</anchor>
      <arglist>(const Construct &amp;options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SignalHandler</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>af94f95bfc7335a16934c6d8c6e2a9008</anchor>
      <arglist>(signal_function_callback_t function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SignalHandler</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>ac5b3f2644de10563a0c1bdaa181ef80f</anchor>
      <arglist>(signal_action_callback_t action)</arglist>
    </member>
    <member kind="function">
      <type>const struct sigaction *</type>
      <name>sigaction</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>a3f01b0753f2bdd2f8bcb2a918feb6f4a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SignalHandler</type>
      <name>default_</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>ae0cc275cf1304262a011c8ce7088d436</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SignalHandler</type>
      <name>ignore</name>
      <anchorfile>classthread_1_1_signal_handler.html</anchorfile>
      <anchor>a0a67ed1ceb31b410ca0c45b0892c4189</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::SignalHandler::Construct</name>
    <filename>classthread_1_1_signal_handler_1_1_construct.html</filename>
  </compound>
  <compound kind="class">
    <name>thread::Thread</name>
    <filename>classthread_1_1_thread.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Thread::Attributes</class>
    <class kind="class">thread::Thread::Construct</class>
    <member kind="enumeration">
      <type></type>
      <name>DetachState</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a664f458a081e0032836bf3de798753c4</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_thread.html" anchor="a664f458a081e0032836bf3de798753c4ab9e5e065a77ab703e16e5dcd0f34f131">joinable</enumvalue>
      <enumvalue file="classthread_1_1_thread.html" anchor="a664f458a081e0032836bf3de798753c4ab0398fd2e0c78072a48131f810266119">detached</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>IsInherit</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a48e6e0cff03495a340a7033cf84e235a</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_thread.html" anchor="a48e6e0cff03495a340a7033cf84e235aa7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classthread_1_1_thread.html" anchor="a48e6e0cff03495a340a7033cf84e235aaa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ContentionScope</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a789bcec59e2258c5ebb2312c56b1fc99</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_thread.html" anchor="a789bcec59e2258c5ebb2312c56b1fc99a54b53072540eeeb8f8e9343e71f28176">system</enumvalue>
      <enumvalue file="classthread_1_1_thread.html" anchor="a789bcec59e2258c5ebb2312c56b1fc99a5075140835d0bc504791c76b04c33d2b">process</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CancelType</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a0240a74c1e10b41f5243c363a4b41b05</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_thread.html" anchor="a0240a74c1e10b41f5243c363a4b41b05a43fff3df3fc0b3417c86dc3040fb2d86">deferred</enumvalue>
      <enumvalue file="classthread_1_1_thread.html" anchor="a0240a74c1e10b41f5243c363a4b41b05a148b8d2facfd6d8883a4273f4553ebef">asynchronous</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>CancelState</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a94e8590e6bdc64e5c870c44235f7cc10</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_thread.html" anchor="a94e8590e6bdc64e5c870c44235f7cc10a208f156d4a803025c284bb595a7576b4">enable</enumvalue>
      <enumvalue file="classthread_1_1_thread.html" anchor="a94e8590e6bdc64e5c870c44235f7cc10a0aaa87422396fdd678498793b6d5250e">disable</enumvalue>
    </member>
    <member kind="typedef">
      <type>Sched::Policy</type>
      <name>Policy</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a6a6f750ac99ad4b411e01eda0f4ea923</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ContentionScope</type>
      <name>Scope</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>adb761ec74ed06beefa8e7a950c4bc1a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void *(*</type>
      <name>function_t</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>ac8a4c2a5c78aede89f189557064e84d2</anchor>
      <arglist>)(void *)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a973380673e9365da7695614db9e59526</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a62f532ad77f44e44b504dfeba1715ba5</anchor>
      <arglist>(const Thread &amp;thread)=delete</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>aaa21802781d0cb796103f88c3c004634</anchor>
      <arglist>(const Thread &amp;thread)=delete</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a26666606f982ace8de54207ff4df8329</anchor>
      <arglist>(Thread &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a43647ab424aaf3c876d831a2975e17b5</anchor>
      <arglist>(Thread &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;&amp;</type>
      <name>move</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>ad7dd677488816357477340d8106d5e95</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>ae2bea61e2ec8ab870073d2577617e996</anchor>
      <arglist>(const Construct &amp;options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a89d43614ef8e31332c523d9a33a86a7b</anchor>
      <arglist>(const Attributes &amp;attributes, const Construct &amp;options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a5669926d42324693a9fd7ae4ba5ec7f2</anchor>
      <arglist>(const Attributes &amp;attributes, void *argument, function_t thread_function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>acd429cd83e7e82b996fec26f33ef744b</anchor>
      <arglist>(void *argument, function_t thread_function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Thread</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a5cc06f9b6a7fe494e0f64e4476117255</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>pthread_t</type>
      <name>id</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>aaae34693665ccae305f592f2bd930869</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a91a221404643bc304adeca4168446c17</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;</type>
      <name>set_sched_parameters</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a8a7848bf52b16c65d163bd14e4553383</anchor>
      <arglist>(Sched::Policy policy, int priority)</arglist>
    </member>
    <member kind="function">
      <type>Sched::Policy</type>
      <name>get_sched_policy</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a86a4663c4ba87a3309090dceded2e22e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_sched_priority</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a73f00ca278c5e05d956813e4cc3df329</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Thread &amp;</type>
      <name>cancel</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>aa3012d4aae50eb90d127310ceff59f6e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;</type>
      <name>cancel</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a5bbda98e9b263130471e74d40a43dbd3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_running</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>aae8ee3a459340b1f0b698d742f6e6a09</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const Thread &amp;</type>
      <name>kill</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a7ca6868e3da9d236dd35b9c43ed0adbc</anchor>
      <arglist>(int signal_number) const</arglist>
    </member>
    <member kind="function">
      <type>Thread &amp;</type>
      <name>join</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>afabd1017a544728b2731e9b61cf0ba35</anchor>
      <arglist>(void **value=nullptr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_joinable</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>a7745be18420305cf6fe414a382697e72</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CancelType</type>
      <name>set_cancel_type</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>af77bd0ff8d9e5b8f185b89d786483b84</anchor>
      <arglist>(CancelType cancel_type)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CancelState</type>
      <name>set_cancel_state</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>abfea2c16bf60991a3fb290b37a5a1541</anchor>
      <arglist>(CancelState cancel_state)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static pthread_t</type>
      <name>self</name>
      <anchorfile>classthread_1_1_thread.html</anchorfile>
      <anchor>ad242d4fe7c2d6b19df2ae8ba858664a0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Thread::Attributes</name>
    <filename>classthread_1_1_thread_1_1_attributes.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type></type>
      <name>Attributes</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a4896ad7bdfac4c8b3c8fec2a964f3535</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Attributes</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>aad775b9fa8aa1eac2fed0cb1a5ea59d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_stack_size</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a81369ac787e013b2e0a0ed29d5f32a6d</anchor>
      <arglist>(size_t value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_stack_size</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a56e1b92767db0e45a7b716086eac0121</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_detach_state</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>ac18ec36c3d34898c5440327ad2f231cf</anchor>
      <arglist>(DetachState value)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_joinable</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>ab8bb2ac4015e38958a44d3c8c1a6e7d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_detached</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>af5279370ff4a82b5fb633601ad4dbcfa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>DetachState</type>
      <name>get_detach_state</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a49ed8ada781bb45c985d5745379b30ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_inherit_sched</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>ae8bd2a77e11d15030c9bf825ed116af1</anchor>
      <arglist>(IsInherit value)</arglist>
    </member>
    <member kind="function">
      <type>IsInherit</type>
      <name>get_inherit_sched</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a5cd3a4fa7f531d687e83ac873ad02bca</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_scope</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>aa9c894d01175f872f70c9099716324cd</anchor>
      <arglist>(ContentionScope value)</arglist>
    </member>
    <member kind="function">
      <type>ContentionScope</type>
      <name>get_scope</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a34ae6aaec3bf986f250b35170b0524c3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_sched_policy</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a906bf2fc2b8214351dc116ceaa89f498</anchor>
      <arglist>(Sched::Policy value)</arglist>
    </member>
    <member kind="function">
      <type>Attributes &amp;</type>
      <name>set_sched_priority</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a9591b2f02c71ce96384f363686458d9e</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>Sched::Policy</type>
      <name>get_sched_policy</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>a25c5888bf349fa8e900aaf443cac0efb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_sched_priority</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>abbaf0d523d1601d4915f4a656a93c098</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Thread</name>
      <anchorfile>classthread_1_1_thread_1_1_attributes.html</anchorfile>
      <anchor>adbc148eaddd341d7ae4d07c9e9e33bfd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Thread::Construct</name>
    <filename>classthread_1_1_thread_1_1_construct.html</filename>
  </compound>
  <compound kind="class">
    <name>thread::Timer</name>
    <filename>classthread_1_1_timer.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">thread::Timer::Alarm</class>
    <class kind="class">thread::Timer::Info</class>
    <class kind="class">thread::Timer::SetTime</class>
    <member kind="enumeration">
      <type></type>
      <name>Flags</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a29a565646f1005b4a4fa4fe2baaa5789</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_timer.html" anchor="a29a565646f1005b4a4fa4fe2baaa5789a37a6259cc0c1dae299a7866489dff0bd">null</enumvalue>
      <enumvalue file="classthread_1_1_timer.html" anchor="a29a565646f1005b4a4fa4fe2baaa5789a96e38ccad4354c423aaa17cb16fdede1">absolute_time</enumvalue>
    </member>
    <member kind="typedef">
      <type>chrono::ClockTime::ClockId</type>
      <name>ClockId</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>adee27f9dee436bff3fe5ab2bc3d524c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Timer</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>aa083fe65cb0fc4f851b574a529472890</anchor>
      <arglist>(Signal::Event &amp;signal_event, ClockId clock_id=ClockId::realtime)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Timer</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a52daf04d586ab09306d179be5b95345d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Timer</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a188ce244d4df25c598ca5f4c5004a1bf</anchor>
      <arglist>(const Timer &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>Timer &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a7c5583484d11d7e1d4acdcbe58d68b35</anchor>
      <arglist>(const Timer &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Timer</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a33d4c57febd5c55a3c6b77557a2523a6</anchor>
      <arglist>(Timer &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Timer &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a53d104c53eb7ce9b3cbbdd8771b91c1e</anchor>
      <arglist>(Timer &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a9b072ed9b47c7e638d0e0e9130aea414</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Timer &amp;</type>
      <name>set_time</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a5f79b5e5446b85ca00de52ebc48238f1</anchor>
      <arglist>(const SetTime &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Info</type>
      <name>get_info</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>a9f2ed6676edd2984c45231a03e725709</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static chrono::ClockTime</type>
      <name>alarm</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>ad8f37ba670d8ee52dfe2e33026ee123f</anchor>
      <arglist>(const Alarm &amp;options)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>cancel_alarm</name>
      <anchorfile>classthread_1_1_timer.html</anchorfile>
      <anchor>af28e84af8709693459c05fea8ce1bb34</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Timer::Alarm</name>
    <filename>classthread_1_1_timer_1_1_alarm.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Type</name>
      <anchorfile>classthread_1_1_timer_1_1_alarm.html</anchorfile>
      <anchor>a857d0ee4060e25c72c8e63e58ad12a69</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_timer_1_1_alarm.html" anchor="a857d0ee4060e25c72c8e63e58ad12a69a783e8e29e6a8c3e22baa58a19420eb4f">seconds</enumvalue>
      <enumvalue file="classthread_1_1_timer_1_1_alarm.html" anchor="a857d0ee4060e25c72c8e63e58ad12a69aeb9ccebea2d1ee9d864838706509286f">useconds</enumvalue>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Timer::Info</name>
    <filename>classthread_1_1_timer_1_1_info.html</filename>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Timer</name>
      <anchorfile>classthread_1_1_timer_1_1_info.html</anchorfile>
      <anchor>a50de43af5bed41f30c071d8cce0e81bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>thread::Timer::SetTime</name>
    <filename>classthread_1_1_timer_1_1_set_time.html</filename>
  </compound>
  <compound kind="class">
    <name>thread::UnnamedSemaphore</name>
    <filename>classthread_1_1_unnamed_semaphore.html</filename>
    <base>SemAccess&lt; UnnamedSemaphore &gt;</base>
    <member kind="enumeration">
      <type></type>
      <name>ProcessShared</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a98cf198a0836a9762fca9b3af854cf61</anchor>
      <arglist></arglist>
      <enumvalue file="classthread_1_1_unnamed_semaphore.html" anchor="a98cf198a0836a9762fca9b3af854cf61a7fa3b767c460b54a2be4d49030b349c7">no</enumvalue>
      <enumvalue file="classthread_1_1_unnamed_semaphore.html" anchor="a98cf198a0836a9762fca9b3af854cf61aa6105c0a611b41b08f1209506350279e">yes</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>UnnamedSemaphore</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a7dd6d553d61be613b3cc0861954bb3c7</anchor>
      <arglist>(ProcessShared process_shared, unsigned int value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UnnamedSemaphore</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a5306d8cd59afe82f5131cf68a163becf</anchor>
      <arglist>(const UnnamedSemaphore &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type>UnnamedSemaphore &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a06079b20ec080590f8545e31eaf6f499</anchor>
      <arglist>(const UnnamedSemaphore &amp;a)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UnnamedSemaphore</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a5ec40af713d2d1601277969866ddd0db</anchor>
      <arglist>(UnnamedSemaphore &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>UnnamedSemaphore &amp;</type>
      <name>operator=</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>adb179111f6383296d64c16683684d5df</anchor>
      <arglist>(UnnamedSemaphore &amp;&amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~UnnamedSemaphore</name>
      <anchorfile>classthread_1_1_unnamed_semaphore.html</anchorfile>
      <anchor>a1fb91b4e83e78efa7de1084db9084f99</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Array</name>
    <filename>classvar_1_1_array.html</filename>
    <templarg>typename T</templarg>
    <templarg>size_t SizeValue</templarg>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>af6ccb876c04ec87beca9451f0caf35e1</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ab9ba9a856faf89b280ffd0bd4810de71</anchor>
      <arglist>(const std::array&lt; T, SizeValue &gt; &amp;array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ae8d52b1c9606ef0e0572a22d107440b3</anchor>
      <arglist>(std::array&lt; T, SizeValue &gt; &amp;&amp;array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ae9b51f83c8f1a811cc1cad1b7937f7ea</anchor>
      <arglist>(std::initializer_list&lt; T &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>acb80ba889f18d0f3c4fc1333f32351c3</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ac148040cbc8e07fde88818246b6b4672</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>abdcc8f4f38a8c12e92e066ff352e2e7a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a48c4f7b26ab96440e8eca4cbe2c5639e</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>adcbe33c69346a3ca76ce435a41a0c114</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a07e27a0afbfde10772868e48a3d9d7dd</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a6e90618279ceb19b3186d108034ce2ee</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a71f51e0efe5e81ad0c24fab81cb8254d</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a49b5a19cde8aa1d3f30f73f44f665e31</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a7e6c04bd5f30944dea9a26bae73dcf6c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a1f0313b849113fe8e4d73573c818ea97</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt;::const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a7ed7b53e325039c6162aef0a43fdcb2d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a602d1f1a75ddf2418425c98e7f96c4bf</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a8fc1c61210c9e81542b0c1e31daf8f0d</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a0930f274ac39fa17638130148df9c204</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>aa451c5c6fb7bd4384d6c4cc5c1430b97</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ab5ff52c1c7ecfa3df07875797af0a6a5</anchor>
      <arglist>(const Array &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a5b662a274cc59b5386f114754c444418</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>aceffb9172c1d495f00e91eb44d2dada6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a2bbe8467358a7ec59fd89d8e0d74f0be</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a69091039a8158885ac0158e277f118df</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>count</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a4b9481cdcc625f3fcd4c591a308ebc5d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a68c62ae253949e61dffc8abdc25964d5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Array &amp;</type>
      <name>fill</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a68dbb4c2417066ee40b7693186628658</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>accumulate</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a2968b2176e0dcd513e1cbd15547bdd4e</anchor>
      <arglist>(T initial_value=T()) const</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; T, SizeValue &gt; &amp;</type>
      <name>array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>aa9296a0b4402dc535a0e86440296571c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::array&lt; T, SizeValue &gt; &amp;</type>
      <name>array</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a9e7289790dbe104457a67c9f69f4702a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ace447fd761b954cf0297a526f79d0c7e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>ab40dfce22f04a32b6720d12104048dfa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>to_void</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a94cfa9bfb6c369e88e5950d9c6ebe3a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>to_const_void</name>
      <anchorfile>classvar_1_1_array.html</anchorfile>
      <anchor>a13ca09ea2b88191b803268d3874454c6</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Base64</name>
    <filename>classvar_1_1_base64.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type>var::String</type>
      <name>encode</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a63b662f48473bc7017ce0896728d20f6</anchor>
      <arglist>(var::View input) const</arglist>
    </member>
    <member kind="function">
      <type>var::Data</type>
      <name>decode</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a683390fbf172dd80f4bc6240ecea501c</anchor>
      <arglist>(var::StringView input) const</arglist>
    </member>
    <member kind="function">
      <type>const Base64 &amp;</type>
      <name>encode</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a5f48ce5923014f9e82ec31174290dfb1</anchor>
      <arglist>(var::View input, var::String &amp;output) const</arglist>
    </member>
    <member kind="function">
      <type>const Base64 &amp;</type>
      <name>decode</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>aa801d535b34d90953b473e8eace37fcd</anchor>
      <arglist>(var::StringView input, var::Data &amp;output) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_t</type>
      <name>get_decoded_size</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>ae9915ae2dd1c89d4b46a43cc05c43b9b</anchor>
      <arglist>(size_t nbyte)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr size_t</type>
      <name>get_encoded_size</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a4b8dcc8eb2e61014470ebd339d4b439d</anchor>
      <arglist>(size_t nbyte)</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Base64Encoder</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a2fcc9d2ab216ad9589f5258400930058</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Base64Decoder</name>
      <anchorfile>classvar_1_1_base64.html</anchorfile>
      <anchor>a2ea3a2b5c30e32df3a681beae396d102</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Base64Decoder</name>
    <filename>classvar_1_1_base64_decoder.html</filename>
    <base>var::Transformer</base>
    <member kind="function">
      <type>int</type>
      <name>transform</name>
      <anchorfile>classvar_1_1_base64_decoder.html</anchorfile>
      <anchor>a45b3303073e3ff1aeccc1955b815d1b1</anchor>
      <arglist>(const Transform &amp;options) const override</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>get_output_size</name>
      <anchorfile>classvar_1_1_base64_decoder.html</anchorfile>
      <anchor>a33eca96dd840ac4b9caaba44eb20bd34</anchor>
      <arglist>(size_t nbyte) const override</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>page_size_boundary</name>
      <anchorfile>classvar_1_1_base64_decoder.html</anchorfile>
      <anchor>a8a7ce35128f4e4db5775eeae642ce3fd</anchor>
      <arglist>() const override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Base64Encoder</name>
    <filename>classvar_1_1_base64_encoder.html</filename>
    <base>var::Transformer</base>
    <member kind="function">
      <type>int</type>
      <name>transform</name>
      <anchorfile>classvar_1_1_base64_encoder.html</anchorfile>
      <anchor>af6c8683c9d2bb7565f6e05595f7239c7</anchor>
      <arglist>(const Transform &amp;options) const override</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>get_output_size</name>
      <anchorfile>classvar_1_1_base64_encoder.html</anchorfile>
      <anchor>ab99d9c3e4b2deebbe18f86c7a9b28b88</anchor>
      <arglist>(size_t nbyte) const override</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>page_size_boundary</name>
      <anchorfile>classvar_1_1_base64_encoder.html</anchorfile>
      <anchor>aac1685cc41de1402a9075b5e3bc4b08c</anchor>
      <arglist>() const override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Bits</name>
    <filename>classvar_1_1_bits.html</filename>
  </compound>
  <compound kind="class">
    <name>var::ContainerObject</name>
    <filename>classvar_1_1_container_object.html</filename>
    <templarg>class Derived</templarg>
    <templarg>typename Container</templarg>
    <templarg>typename T</templarg>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type>Container::const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>aeafe619fca6f2ff62016d1b0e69c4c2d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a0bdb397aa61a0973e93a20ed1518173c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a74663bdc45dc954ab852d94d6bb62e4d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a3142fa7d8c24d8e5f08b677c18cc03fd</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a303c50edb81622b4a6648c0339e78a31</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>ac5b6fd5cd8c54ead5d4f5069b1b8baa7</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>ac244b52d2a39aa033e1f598818eb31fd</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a8edfc7b0bbfd50c337a307dec9fe6907</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a5ae25468abfe18169ce0677ec783626e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a8942f203e0e1376fe69ce7df4d9040c6</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a85d8917cb3c153243f2726043a24eb2a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>Container::const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>ac2ffc25b7c5601d7a71d872c0fca7bf6</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>accumulate</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>a5573c8204c444087cd0d49445b296e65</anchor>
      <arglist>(T initial_value=T()) const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Container</type>
      <name>m_container</name>
      <anchorfile>classvar_1_1_container_object.html</anchorfile>
      <anchor>ae2d590d238c0a52b9c8b62007d58024a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Data</name>
    <filename>classvar_1_1_data.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">var::Data::Copy</class>
    <class kind="class">var::Data::Erase</class>
    <member kind="function">
      <type></type>
      <name>Data</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a237fa6ebd27eea52083c71f3b7c34aaa</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Data</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>aa6eeb3d01649dec66ae284241fa687ee</anchor>
      <arglist>(std::initializer_list&lt; u8 &gt; il)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Data</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a564d0dd9041939a58396c54979f31972</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>add_null_terminator</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>afe998fd4d7154c59c952c83b7a8b967f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>capacity</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a8e07955806e72210065b6dfc428ba463</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>resize</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>aae802d83a28ac117dc76dee2bdb3dcd7</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>free</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>ad5d2f2a6b0bdf05102b5876daff44e74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>copy</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a1577fccaf7e2633e443cf8eb0d45b2f2</anchor>
      <arglist>(View a, const Copy &amp;options=Copy())</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>append</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a94d3cc1ca216a78f3865044d968d3b10</anchor>
      <arglist>(View view)</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>erase</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a2b166c95ef58a3af067061a6325a7bb5</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a14e6078bb0a56f61db5f6089c92f9685</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Data &amp;</type>
      <name>reserve</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a95241179affcf7c93d6b86eae9357c7e</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>add1a0025b34c1bcf7c37c37bc2599c4c</anchor>
      <arglist>(const var::Data &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a291e3b3185b6f1d8e19dddc1d8dd99b2</anchor>
      <arglist>(const var::Data &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a93b4d1eb09e3ceb48547f730e30ac07e</anchor>
      <arglist>(const var::Data &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a272cbaae92f11e34c90a9d61843acc5b</anchor>
      <arglist>(const var::Data &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a53f2a6f615422a030603cfa4166deb02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a30731746ba74f6fb0b476ac5cbcc8bef</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u8 *</type>
      <name>data_u8</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a491be71ba9a737145e300fd4eac4d06a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const u8 *</type>
      <name>data_u8</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a9c4401f94ee7a2c99150399afd5b37ed</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>View</type>
      <name>view</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a194b81e60173ea96f918e2a0c7947569</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>View</type>
      <name>view</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>adb0a75623a5d5ee89f1a34a671c25786</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>size</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a6391f76a1fa5c6836a8da53678682ea7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>size_signed</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a089a026764cdcdd2ef1f2e46e501353a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>string_view</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>aafa9326bfcbe4a0a8e54843cbd0e2ce6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Data</type>
      <name>from_string</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a4792ae5e84f1809c55457531e6ee1b15</anchor>
      <arglist>(var::StringView value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static u32</type>
      <name>minimum_capacity</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>ad9d826e0a2666c504220d827b549c905</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static u32</type>
      <name>block_size</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>a303af48def9fe8d2b28da5ca23e4f331</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>reclaim_heap_space</name>
      <anchorfile>classvar_1_1_data.html</anchorfile>
      <anchor>ac6a7d1a9a7657252dd3d6601e3651e7c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Data::Copy</name>
    <filename>classvar_1_1_data_1_1_copy.html</filename>
    <member kind="function">
      <type></type>
      <name>Copy</name>
      <anchorfile>classvar_1_1_data_1_1_copy.html</anchorfile>
      <anchor>a418a28396612bef9e35dd3e736ca867e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Data::Erase</name>
    <filename>classvar_1_1_data_1_1_erase.html</filename>
  </compound>
  <compound kind="class">
    <name>var::DataInfo</name>
    <filename>classvar_1_1_data_info.html</filename>
    <member kind="function">
      <type></type>
      <name>DataInfo</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>a0c7bdf9d46c69857106f99690df1d1b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>arena</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>a5039482e3104d3aabdb1121cc5323724</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>free_block_count</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>a479af12876822c3f54b52fbf6227ad11</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>free_size</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>a326eb68d964dc01b8fe5e4e9994691bb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>used_size</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>abba0d863ea342384bb69138ee1c1e49d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_data_info.html</anchorfile>
      <anchor>a6eda5f5d75c21dcb478d4c8d5cde1d01</anchor>
      <arglist>(const DataInfo &amp;a) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Deque</name>
    <filename>classvar_1_1_deque.html</filename>
    <templarg>typename T</templarg>
    <base>api::ExecutionContext</base>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::iterator</type>
      <name>iterator</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a16400639882fa14ff38e8e0040e2d83b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>aef4a12cd10c5e1f5ba530ffb44c6f459</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a031bad139b2cb1985a356257ba70519f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a4e96aa7fc80371d6755c897a18b8866d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a1930790791d634c861481ac19a759954</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>afba282b7dffac1e73efb7881b5750a52</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a830627e7fdadf2554533641f8088a1c3</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a76b62c74f8bf464a1782588356f57e70</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>aaaace24ea9ff3c2f9dd98315defdf636</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>ad8c8df0388ea7e379a6891627307ecd1</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a2e127bc6e16f1a4785a5f203672ba3fa</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a1eab6614b20312d62768a794f9a741bb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a1604a6081c6197d5d0c62a2c5f5a8274</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>abdec9d4b962664e16e66beef8fa43da1</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a1900ba725940e81e186b7d057a23f6cf</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a392582541bb3a14510e5e3baac88c7f2</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a3b9ed1f9c33adbefca2fab45009bfde2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>afcfd7493b682730f09368a58ff50f0ca</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>af38e161532649c3576b6a5b349ee9832</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a28ce4b1407a5a7eef340c3510d78a992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Deque &amp;</type>
      <name>push_front</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>af7848f41cd9928caa321e2cd36cec877</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Deque &amp;</type>
      <name>push_back</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a13887d4244aa7d57c64f8778548c4cb9</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Deque &amp;</type>
      <name>pop_front</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a685971da31f783e774dc662193c1b071</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Deque &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>aa831b99d931e2be2e2ae6610b8e7eda6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>a2e8363f3e1dbe126301f350bef0bb73f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>ac3a29e23b3f8ef5847f89def57ee90a0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Deque &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_deque.html</anchorfile>
      <anchor>ab9d1aa7053f6abe0413b0fe317356d90</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::GeneralString</name>
    <filename>classvar_1_1_general_string.html</filename>
    <base>StackString&lt; GeneralString, VAR_API_GENERAL_STRING_SIZE &gt;</base>
    <member kind="function">
      <type></type>
      <name>GeneralString</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>a8ebecd190a951585672008a15a7784cf</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GeneralString</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>a31762e53ee9e3a35523900655c0e0c02</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GeneralString</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>a6328de762b770bf1c485dcdbec0ba8e2</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>adfcab7893158518ba62fa8ec4954526f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>GeneralString &amp;</type>
      <name>operator|=</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>ab885b6804c2ef3843319a38964d85bdd</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type>GeneralString</type>
      <name>operator|</name>
      <anchorfile>classvar_1_1_general_string.html</anchorfile>
      <anchor>a1624894e274b867f3a5d6a1a7d802ca4</anchor>
      <arglist>(const var::StringView a)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::IdString</name>
    <filename>classvar_1_1_id_string.html</filename>
    <base>StackString&lt; IdString, 24 &gt;</base>
    <member kind="function">
      <type></type>
      <name>IdString</name>
      <anchorfile>classvar_1_1_id_string.html</anchorfile>
      <anchor>a8921533f9cd4a3a80f27c77f0b100dfc</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IdString</name>
      <anchorfile>classvar_1_1_id_string.html</anchorfile>
      <anchor>a543359676e6f2ec993eaa8777269845d</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IdString</name>
      <anchorfile>classvar_1_1_id_string.html</anchorfile>
      <anchor>aeb5c4afac779a4126c6e83ab3d602c91</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_id_string.html</anchorfile>
      <anchor>ae2a364236f7216a4501fe6f1fe3cc98c</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::KeyString</name>
    <filename>classvar_1_1_key_string.html</filename>
    <base>StackString&lt; KeyString, 48 &gt;</base>
    <member kind="function">
      <type></type>
      <name>KeyString</name>
      <anchorfile>classvar_1_1_key_string.html</anchorfile>
      <anchor>a82fb773396cf5a2963cf26e423c28bd0</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KeyString</name>
      <anchorfile>classvar_1_1_key_string.html</anchorfile>
      <anchor>a4b0ce93362f4f879d978c17b40f0660f</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KeyString</name>
      <anchorfile>classvar_1_1_key_string.html</anchorfile>
      <anchor>afb0b652c42e03c07aa97c4949448abfe</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_key_string.html</anchorfile>
      <anchor>a864f7ecfa151e04e836ba0c8209264ac</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Matrix</name>
    <filename>classvar_1_1_matrix.html</filename>
    <templarg>typename T</templarg>
    <base>Vector&lt; var::Vector&lt; T &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a926dbf9c6b42c76190fff879ebf3a0cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a890b7806e91da6a22bded513f8dc9cbe</anchor>
      <arglist>(u32 row_count, u32 column_count)</arglist>
    </member>
    <member kind="function">
      <type>Matrix</type>
      <name>transform</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>ae5dcddb5d8836a98a2c4fd5dd38a57e8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Matrix &amp;</type>
      <name>resize</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a59c27421492013a5101cd1286cbca668</anchor>
      <arglist>(u32 row_count, u32 column_count)</arglist>
    </member>
    <member kind="function">
      <type>Matrix &amp;</type>
      <name>append</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>aeaef795f8fda94b346df5a61f5af226a</anchor>
      <arglist>(const var::Vector&lt; T &gt; &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>var::Vector&lt; T &gt; &amp;</type>
      <name>row</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a49bd873022241a3a8f77731d719e5102</anchor>
      <arglist>(u32 row_offset)</arglist>
    </member>
    <member kind="function">
      <type>const var::Vector&lt; T &gt; &amp;</type>
      <name>row</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a41a5017a55c98ffa271c15827f7d1f1e</anchor>
      <arglist>(u32 row_offset) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a30ae7c6e014c0da0caf08c1b5a4228fa</anchor>
      <arglist>(u32 row_offset, u32 column_offset)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>abee96a14a5ecf357b704e6c91fe450df</anchor>
      <arglist>(u32 row_offset, u32 column_offset) const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>row_count</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>a78743d3e32b415c153575fd659585007</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>column_count</name>
      <anchorfile>classvar_1_1_matrix.html</anchorfile>
      <anchor>ac2abecd6a305d92e223b8325a631a5c0</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::NameString</name>
    <filename>classvar_1_1_name_string.html</filename>
    <base>StackString&lt; NameString, NAME_MAX+1 &gt;</base>
    <member kind="function">
      <type></type>
      <name>NameString</name>
      <anchorfile>classvar_1_1_name_string.html</anchorfile>
      <anchor>a2decf546b2c0d09209990561a8158b0b</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NameString</name>
      <anchorfile>classvar_1_1_name_string.html</anchorfile>
      <anchor>aa6989c38505cde78963efab12bbf7230</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NameString</name>
      <anchorfile>classvar_1_1_name_string.html</anchorfile>
      <anchor>aff81e784c182c2af2c736f62df83a162</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_name_string.html</anchorfile>
      <anchor>ae2c7ffe3d8fedb8db44f443058d1d07a</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::NumberString</name>
    <filename>classvar_1_1_number_string.html</filename>
    <base>StackString&lt; NumberString, 64 &gt;</base>
    <member kind="function">
      <type></type>
      <name>NumberString</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>af0b9f6ebb96e90379bb294c95b007d80</anchor>
      <arglist>(T value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NumberString</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>a8ce1dfaae629acf060538ddc5357e90c</anchor>
      <arglist>(T value, const char *format)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NumberString</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>a94411ec0799556a8f6286615c6a74bc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NumberString</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>ac241da664b13028a7ae03f013fabede6</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NumberString</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>ad896447f5f7b8d109a4e99dc971d1648</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>to_integer</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>ab31f6e8b48d8b75f530d0d2b7025ab9b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>to_float</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>a3151b97c6e8842f9eef0aaddcc55062b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>to_long</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>ad6acb52b035636f8c07ba0407da46920</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>to_unsigned_long</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>a9d1dcb93b745b56d878ecfee5a5b493f</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_number_string.html</anchorfile>
      <anchor>a1d1bc084be0dddd65784448c09590578</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Pair</name>
    <filename>classvar_1_1_pair.html</filename>
    <templarg>typename T</templarg>
    <base>Array&lt; T, 2 &gt;</base>
    <member kind="function">
      <type></type>
      <name>Pair</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>a389ecb2688fadebea9ec9f53e63e2915</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Pair</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>a373add36f7adf6f29693493946dfe16d</anchor>
      <arglist>(const T &amp;k, const T &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>key</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>ab3ddf47b28e8c7653ef03a42b410da56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>key</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>a9a408e3cddb81581668dece4730752f0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>value</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>ac2f3ed2892559da15c6180069ffbdeff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>value</name>
      <anchorfile>classvar_1_1_pair.html</anchorfile>
      <anchor>a3788e8675f2c0669a23ae9be32a031e8</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::PathString</name>
    <filename>classvar_1_1_path_string.html</filename>
    <base>StackString&lt; PathString, PATH_STRING_LENGTH &gt;</base>
    <member kind="function">
      <type></type>
      <name>PathString</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a863891799c999a590a7eb6a50e426d87</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathString</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a126398e290843404a2bd69221a8282c7</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathString</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a6b216dad4efa9daf041df48fcae09dee</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="function">
      <type>PathString &amp;</type>
      <name>operator&amp;=</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>ac4af28bc48d0520f13c346d805c8c100</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator/</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a9d5ddbec396aadd87a46ee3490dc3f49</anchor>
      <arglist>(const var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator&amp;</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a777c89c548224e1002d1f356548dd411</anchor>
      <arglist>(const var::StringView a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const char *</name>
      <anchorfile>classvar_1_1_path_string.html</anchorfile>
      <anchor>a3034be265f9632cd32fc8ee775555589</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Queue</name>
    <filename>classvar_1_1_queue.html</filename>
    <templarg>typename T</templarg>
    <base>api::ExecutionContext</base>
    <class kind="class">var::Queue::Erase</class>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::iterator</type>
      <name>iterator</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a3bd29a2729b8d4c5d158a0114aa35347</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a6d274ef0f9b51623b84470fb0e11d0cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::deque&lt; T &gt;::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a3fd8cce5d2500112ded4c38ea862973b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a276115e624907650418b4406b7189b56</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Queue</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>aaa4db50b6cfabb9198ad7b59de65af64</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>aee51d67297cacedb1ed902b58ec3a45d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a00c4dc295ab0a888667e0e76bf537a55</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ae667c08616b70abeb58b3a7e9f72053a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>af854cef2198d9da37567dec180b54bec</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>aeec2c87e501b83c3bf66c5d43dfd8d2a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ae08e597d9b159c01b0702d1881d00d73</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a2fcd3e98ee4e567fc141a8449bee5886</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a9806767ad887fa9ed086664592b4e78e</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ab4fc72f6432b1e9a333a57985ea18e5e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a0137b077d779bc9dc25e3856e786ca65</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a5db51f17c0ac77308388bad3ccb8287e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a057a9cd077c77dc82c879d62c0614a57</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>af6b77a8ed7ddb877e467f6a990a2f834</anchor>
      <arglist>(const_iterator position, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a77a4318f0dcfb454572bbcb8fd58c4ea</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a05f525bc67a01360f366873a02b29da1</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>adb7e0364796a7c8a207b3a8de7d917bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ad2a3c5e684713c08e99e04c6b1e25f4b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a4bab0509e20fa49551b48ade1dd67c71</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a206f5223800950fd88d4145a3a91b467</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>push</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ae7f555f2f36f0ad17a8e2c6dbc8ba236</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>pop</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a44e83490cf7c74b0b07607cfd89acd64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>erase</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a3aa37b641671e86a2110595a4d454caf</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a4086d3057a8eb7706aa9082ee3425455</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>remove</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a64c30c41ad9cf343d6183a1a99d6bd7f</anchor>
      <arglist>(u32 pos)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_offset</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a0895a91de1324761f732ef4425b82c07</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>find</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ae00ddf410b5f1f8964fb1b5d584f5c52</anchor>
      <arglist>(const T &amp;a, const T &amp;not_found=T()) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>ab61123c6ab0aa63f0ce9dc3cb7e2cdf3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>aa1467c84e4e722355461270945a82201</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Queue &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>a478e6affb64fc3e4388d48bb34208bd7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>accumulate</name>
      <anchorfile>classvar_1_1_queue.html</anchorfile>
      <anchor>adb201f3c8ad494b6258fad133ef68a83</anchor>
      <arglist>(T initial_value=T()) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Queue::Erase</name>
    <filename>classvar_1_1_queue_1_1_erase.html</filename>
  </compound>
  <compound kind="class">
    <name>var::Ring</name>
    <filename>classvar_1_1_ring.html</filename>
    <templarg>typename T</templarg>
    <templarg>size_t item_count</templarg>
    <member kind="typedef">
      <type>Array&lt; T, item_count &gt;</type>
      <name>Buffer</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>ab592c07b9bb4a854efc7c204faa7fc76</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ring</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>aae88123ee01954e94c12812af0d784c4</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Ring</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>adc7121d50304f19018d44673614e4f69</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count_ready</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a9333bba2a35500681bcaaf0b0ae69893</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_full</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>afba1c2ddaacd85100c046233e87cfa1f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a5f636fef2024a3d77f80bf7e181ae3e5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Ring &amp;</type>
      <name>set_overflow_allowed</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a15712de3cebbf9edf2a270d90f3b6b0a</anchor>
      <arglist>(bool value=true)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>ae4d48f903d0f91251fb03cd3fdeaaea4</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a1c8318f200d1ede4c44daf1df205d6b6</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a556a5afbcbae2ab938c6efa055bde06c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a9bb61f4c3c7d0c9190bfb4bae9fe3bef</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a0cf2e3af38229848a529b772c2d224f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a6886a3fd227d433f72e6b4da8943485e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Ring &amp;</type>
      <name>push</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a24e9473c11af896dc655a50019d7945c</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Ring &amp;</type>
      <name>pop</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a623a8d8ee301d99b832428be990f91cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Array&lt; T, item_count &gt;</type>
      <name>to_linear_data</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a14f31593ff6f8b11485bf45939591483</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Ring &amp;</type>
      <name>rotate_forward</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a2b8c5f1a5a03a24a0ce1217a59b9a162</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ring &amp;</type>
      <name>rotate_backward</name>
      <anchorfile>classvar_1_1_ring.html</anchorfile>
      <anchor>a75b6249912effa1819ac5f30b3a47e81</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Stack</name>
    <filename>classvar_1_1_stack.html</filename>
    <templarg>typename T</templarg>
    <base>api::ExecutionContext</base>
    <member kind="function">
      <type>T &amp;</type>
      <name>top</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a0075b57792c0c8271f17e3c8b44aaee7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>top</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a7bcd695b2354f030cd321fe9676b506a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Stack &amp;</type>
      <name>push</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a22a3038321c0b22022605e1d26889bc9</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Stack &amp;</type>
      <name>pop</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a8a6d9d164275395eb59d7b99bb834027</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a3416cd224b1a20324e99d2b5df91a809</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a04a01b3a8f2bf02801ca1d7c2c0bb62c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Stack &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_stack.html</anchorfile>
      <anchor>a6a69472ccaa45cb6b3e12017ff94898a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::StackString</name>
    <filename>classvar_1_1_stack_string.html</filename>
    <templarg>class Derived</templarg>
    <templarg>int Size</templarg>
    <class kind="class">var::StackString::Replace</class>
    <member kind="typedef">
      <type>StringView::Base</type>
      <name>Base</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a9ceb6aa6a5329ac97932493cbba50572</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a9c576958086a82507ab3d3a0f900754d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a4837e5e5acc337eb88c8348885ad8d01</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>append</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a90bc48e9f85f3915418eea0b645fec34</anchor>
      <arglist>(const char a)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>append</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a3fdacf768831127c5717e925d304bc89</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>length</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a54567000529855d01f921072fa826b9a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>back</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ae0d4754e8bc082b08068a92b9499018b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Derived</type>
      <name>operator*</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ab87eb5df10f25477392ebd3075a2aa4b</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a88fa6167a8c8a0127668260e24b6ee4f</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a2c9860343022d5759c9a9c61d4aec891</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>af8def0baadcf12c37d1b91664580af5e</anchor>
      <arglist>(const StackString &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a69238d0f2ab90207680ad6aa1c71521d</anchor>
      <arglist>(const StackString &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a26e35b0846a2718be050843882c41bf4</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a42efabff48c21adfa6f8d146691a563d</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a9a3f269d28e7faba675ce6c7a5643f47</anchor>
      <arglist>(const StackString &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ad70882a2ea81e272196a311fd63721b6</anchor>
      <arglist>(const StackString &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr size_t</type>
      <name>capacity</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a1a28765c4f59cbac3f114bc6ea4a488f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ac2af71b997e22b1c514972323ea6b180</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>cstring</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a13333835d25c67b85ec18cbf90ab7256</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>string_view</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>af5aeb9062b132f1408655fe5af3f6783</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>at</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>aeafed56c61ce2b9b2dffaba0d86e1e5b</anchor>
      <arglist>(size_t offset) const</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>format</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a9c5a279a19ac8d57c3d9a11391398976</anchor>
      <arglist>(const char *format, Args... args)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>to_upper</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ab4fbadc071b0664cbeab9850cc0898c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>to_lower</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ab02f72b33ca04746714bec4965caa5df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>pop_front</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ab404d4e94e06f940ecb52ac917693c72</anchor>
      <arglist>(size_t count=1)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a1c1b56b61c7b1eb1344b7c0d0e3ff117</anchor>
      <arglist>(size_t count=1)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>truncate</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ab31c741882edff83c4a06232e1d68a90</anchor>
      <arglist>(size_t new_length)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>replace</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ae020f401f0923a0c87ba1c18a5ac6181</anchor>
      <arglist>(const Replace &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Derived &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>aa62d5431a113ee4cfc8851379bbf26fb</anchor>
      <arglist>(const Replace &amp;options)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>StackString</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a5b929bd0b01001067857fc962a457d2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>StackString</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>ad0467c93cb791f63c179024080bdceec</anchor>
      <arglist>(const StringView a)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>StackString</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a96cd53b693cce09c1198221e16de897e</anchor>
      <arglist>(const char *a)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char</type>
      <name>m_buffer</name>
      <anchorfile>classvar_1_1_stack_string.html</anchorfile>
      <anchor>a69c76314c7e0c181c3c170b6c3453d2b</anchor>
      <arglist>[Size]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::StackString::Replace</name>
    <filename>classvar_1_1_stack_string_1_1_replace.html</filename>
  </compound>
  <compound kind="class">
    <name>var::String</name>
    <filename>classvar_1_1_string.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">var::String::Compare</class>
    <class kind="class">var::String::Erase</class>
    <class kind="class">var::String::Insert</class>
    <class kind="class">var::String::Replace</class>
    <member kind="typedef">
      <type>StringView::Base</type>
      <name>Base</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>acfa0d7234795884ba43f36fcbd54fc08</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string::iterator</type>
      <name>iterator</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a95efbc9f31739872034286dc3db64c33</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a5302d463fa2282977c4ef550116e0243</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a192c279cbb2638836180d05d84ead2fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ac9b6e0b7728f673ef5af64bacc28dbbb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a3ea9f97b3a5eb071f637d0b66e78c05e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>afa620ff4b68701ec1538edfc8f972f01</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a56e5f9f454b4cfe69af2b4125e035d7a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a3e4b0871ab4be9e9a5bcd8eb74c6975e</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>acb3c1b80340aed5cd9e9d23fcdafe142</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ad6dadea82f21d07a74a95e032793562b</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a0648de0b2af183fb9f34a33caf42c38c</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ac3aeff934e021566a697527c8e232337</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aa08a6e690cc6b16da65fd18343c42fc5</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a7f9f3d20fb9f6647d829082ba65f072a</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>af783598368704c4de6cdfc4a43a88f5b</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a56325f3f836b542a7141fe52322dbd3f</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a0bfb4464fd2aca75f238f5a8cae68c3b</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a380ef5d5a2b6d5297567a17ebcddb792</anchor>
      <arglist>(const char *s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a4e5f44ca51182d603da771e7a4476db8</anchor>
      <arglist>(const Data &amp;data)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a80ad57e0ffb992ed3f310e950888d4c0</anchor>
      <arglist>(StringView s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a6255c4846c37b8f91c5da3fe2f8136e9</anchor>
      <arglist>(const String &amp;s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a6d16bbda5d5cbf4dc4cf6621ef2233c7</anchor>
      <arglist>(const char *s, size_t length)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a10651d3eb3a033085659bf77125dfc36</anchor>
      <arglist>(size_t length, char c)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a1b0ce3c1544ccb868c62c6e89bfedad5</anchor>
      <arglist>(String &amp;&amp;s) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a817f9316feb32f921c99792f9b3e77dd</anchor>
      <arglist>(std::initializer_list&lt; char &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>afc5ac65c735a2234ec9f53ead63d5e3b</anchor>
      <arglist>(const char *s)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>affc9d3e7d9e7ce73a79effa83aa78bd8</anchor>
      <arglist>(const String &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a6ba7152554bb2ac6a692865e66b9e2de</anchor>
      <arglist>(char c)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a5f2572650f34e7642d9c22720d334ff1</anchor>
      <arglist>(const std::string &amp;a)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a07b6a4f2f87a1d8e94f272f16b55aef1</anchor>
      <arglist>(std::string &amp;&amp;s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>String</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a007228736c8c9103aa85759017ee27d8</anchor>
      <arglist>(const var::View &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator+=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>afc5e2096d5713c0559616706c1fd169c</anchor>
      <arglist>(char a)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator+=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aac5ad1317b48bdc89cde92f27158c05a</anchor>
      <arglist>(const String &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator+=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ab1116e437218f2cb2ee0f88f6071e3e0</anchor>
      <arglist>(StringView a)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>append</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>af11241e256d46d0eaada3500c66f36c0</anchor>
      <arglist>(const StringView &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator+=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aa9999120773733783213eeeb5d54982a</anchor>
      <arglist>(std::initializer_list&lt; char &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator*=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a767025cebffdd0732025960cc5fbd76b</anchor>
      <arglist>(u32 a)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator*</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a194aeb320b142e633908ebee7c7db8d8</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a15f6b18947ff444bd5933019ab3bbff6</anchor>
      <arglist>(const String &amp;rhs) const</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ab790a2b1be23d57a139bc077b96fdc21</anchor>
      <arglist>(String &amp;&amp;rhs) const</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>af724991697cce93d8e8108d6c6e61f6f</anchor>
      <arglist>(char rhs) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aa9f8eae8579c813d13da84ac84b14c39</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aeec0f01cb8a26b641ce480f9c70a44f0</anchor>
      <arglist>(const StringView string_to_insert, const Insert &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a556fe128a0e27567c483a27037e275cf</anchor>
      <arglist>(const StringView string_to_insert, const Insert &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>erase</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aa78d6a21fd1eed52f501474882ea2132</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>erase</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ae3f4792d2622b906eba1c38cc6f5f8a4</anchor>
      <arglist>(StringView string_to_erase, size_t position=0)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a0f97775b4ee568d01c3fca0ca8c9a9f4</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>replace</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a9c943c3db1f1e1ba80c47bdee0921aa0</anchor>
      <arglist>(const Replace &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a94bb0d4ccc28fdbaa34e81a4fbc00c23</anchor>
      <arglist>(const Replace &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>count</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a805eb19593d5685a5c6e327a705edd89</anchor>
      <arglist>(var::StringView to_count) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>length</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a8c2c1593115919632c3d7c8cd8f314b0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>length_signed</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>afb600b3dbe2079fce94cd677ff89c088</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a330c3dd061cba6bfed5a57d43a7be276</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>free</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a38f4ab4b6d113cf20d1c8ea7b5b1863f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>push_back</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ad883d52532f158f52bbc7cb69bea86e9</anchor>
      <arglist>(char a)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a9cc19d167b84d1ca6d04cabe00d5da47</anchor>
      <arglist>(size_t pop_size=1)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>pop_front</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>adcabed415cf32660d9734615a17d78e0</anchor>
      <arglist>(size_t pop_size=1)</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a5313e8c2f78d89ddcd87c35b63036fc8</anchor>
      <arglist>(size_t pos)</arglist>
    </member>
    <member kind="function">
      <type>const char &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ab3bafe083dd1882a6c3a1f3f08fa3970</anchor>
      <arglist>(size_t pos) const</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a29588af46aa2fcbe4dde23b0314d141b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a695e76cb3cccf24452fa2b76b6c15d24</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aad636eb0b1cd47e70c5f18c7d49b7b2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a6dc1c22efdf5abab36e75a43a2b0388f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>resize</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a88109a0a3dc33794eddc258ae41a9e6a</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>reserve</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a1fc9b4f65af9be670457379c78392713</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>format</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>abceb571c7fd299924cb332b646c19fe8</anchor>
      <arglist>(const char *format,...)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>vformat</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a4f7d6e7612171732fb83e58de8b81e40</anchor>
      <arglist>(const char *fmt, va_list list)</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>to_upper</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a0b014d84245d0ed2909408635b55e190</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>String &amp;</type>
      <name>to_lower</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a23bfc8a15eb984014986f44a2af625b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>cstring</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>af4c01db291e2d329c6d1f2f01524ffe3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>to_char</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ac4a1d4153256f875a25ed1189ebafd20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compare</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a3420698ae90c6357ce2aa8b19c1245b9</anchor>
      <arglist>(const String &amp;string_to_compare) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>compare</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a42ea1cebae5ec44ee8a4d59df621d122</anchor>
      <arglist>(const String &amp;string_to_compare, const Compare &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ad49bf6236f797da874171e652dbf1201</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>aace66f706100c4e56eaa507bd125f399</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ab87eba974e4b1b6146411622c844592a</anchor>
      <arglist>(StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>af16f9ed763267c69187db732db123982</anchor>
      <arglist>(StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a849580c3832ae072be7d22ae56e8ccab</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a5a0513bbce129035a4445a0074395377</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a0779f5e4d68a1150ef16a727c85d7b2b</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ae7da99159b95aabea48b5ebada62dce8</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a541de968e43da41b219c853385d129d6</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ab00d0ea3cb3cb4640d3e644a12ed132d</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>to_integer</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ad98728c68308e9ef100b884fc137566e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>to_float</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ac4cd9559aa9aae4bf9b7f4c4bbebe3f7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>to_long</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>ac1f853fe611539cee940e105c4e22328</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>to_unsigned_long</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a8de32457626b6eb19ca26e4cbbaad09d</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>capacity</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a334279b0250299719616b96a97b1a019</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringViewList</type>
      <name>split</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a700a5748f28cdbaf0c846616e1aca392</anchor>
      <arglist>(StringView delimiter) const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>string_view</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a64b2a1b6c7bacec74ed47b38b13e5894</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const String &amp;</type>
      <name>empty_string</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>abb7e8aebdfc23c173d0cf699e02a4c7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>constexpr static size_t</type>
      <name>npos</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>afc03049bebc249f850e91e306f7a68c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string.html</anchorfile>
      <anchor>a88f187f82b757743e4a260d55510c637</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::String::Compare</name>
    <filename>classvar_1_1_string_1_1_compare.html</filename>
  </compound>
  <compound kind="class">
    <name>var::String::Erase</name>
    <filename>classvar_1_1_string_1_1_erase.html</filename>
  </compound>
  <compound kind="class">
    <name>var::String::Insert</name>
    <filename>classvar_1_1_string_1_1_insert.html</filename>
  </compound>
  <compound kind="class">
    <name>var::String::Replace</name>
    <filename>classvar_1_1_string_1_1_replace.html</filename>
  </compound>
  <compound kind="class">
    <name>var::StringView</name>
    <filename>classvar_1_1_string_view.html</filename>
    <class kind="class">var::StringView::GetSubstring</class>
    <member kind="enumeration">
      <type></type>
      <name>Base</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ab8ac90a82dd067897c09f9b4da75e5a9</anchor>
      <arglist></arglist>
      <enumvalue file="classvar_1_1_string_view.html" anchor="ab8ac90a82dd067897c09f9b4da75e5a9ae271e2d9f011df547b9b98db5a3f287a">auto_</enumvalue>
      <enumvalue file="classvar_1_1_string_view.html" anchor="ab8ac90a82dd067897c09f9b4da75e5a9a34d0e21ea08f041727cd3c62f02535e3">octal</enumvalue>
      <enumvalue file="classvar_1_1_string_view.html" anchor="ab8ac90a82dd067897c09f9b4da75e5a9abdaa3c20a3e3851599514f7c6be5f62f">decimal</enumvalue>
      <enumvalue file="classvar_1_1_string_view.html" anchor="ab8ac90a82dd067897c09f9b4da75e5a9a2c34788af99f9ca074434e362d584d54">hexadecimal</enumvalue>
    </member>
    <member kind="typedef">
      <type>typename std::string_view::iterator</type>
      <name>iterator</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aa59f7e31268522df8ca81db3d72e6a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string_view::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a76723e736d9eb4bc16f2340ed04b8034</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string_view::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a22a5ba9c8cd020c5c59516e0149d634e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::string_view::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a78235860adca0736dd3bdcc70e59d4cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ac5188eb59deb182f84bc5126aa78e46c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a59e5f1a426eba7f535db31a827c49b79</anchor>
      <arglist>(const char *value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ae3c2deb2b483fb36a6e7afe326cbbeac</anchor>
      <arglist>(const String &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>af38ba5ef1f6b99c6f7495c5387410bac</anchor>
      <arglist>(const IdString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>af4e89f86673c487a658fc1def63aac9a</anchor>
      <arglist>(const KeyString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8c8d8711f3c8e593ed037acc8dd48ae3</anchor>
      <arglist>(const NumberString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a6b74eed6a784072794749d64d56d5083</anchor>
      <arglist>(const PathString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a077c2a35d20d5ef2f5a194995994572e</anchor>
      <arglist>(const NameString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>afc8f1c70657f7060b5ad9feb7ca8ce95</anchor>
      <arglist>(const GeneralString &amp;value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringView</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aecfd0ae76f6ffbcdd0e303af06280506</anchor>
      <arglist>(const char *value, size_t length)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a2474429e117b9317293d136468dfc3f7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringView &amp;</type>
      <name>set_null</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a78cd9ddd58e3e68c3907cd63961dc6ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null_terminated</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ae1c97f4e649fbc03631e16e2b14f349b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>at</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a16dc3f1ad9c743cd3ac7f782afa39a0a</anchor>
      <arglist>(size_t value) const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>front</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a6048899479eabb76268e1810932546a3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>back</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ad561a28e64f39ad948c6ab4d59077d37</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>length</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a1527d3097b5dc5dc8df33dc53e3595be</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aec1ec5054884dc10e3e96d96fd67de6e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringView &amp;</type>
      <name>pop_front</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a4ac982bc42d2aef701b3dd1329339154</anchor>
      <arglist>(size_t length=1)</arglist>
    </member>
    <member kind="function">
      <type>StringView &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a9864297c73047ae3c70b3db9daf10ad3</anchor>
      <arglist>(size_t length=1)</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>get_substring</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8e9d804e50ad2ed58fa6f432a8745fd8</anchor>
      <arglist>(const GetSubstring &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ae314c3509cd512a6a7436d00becea64d</anchor>
      <arglist>(const GetSubstring &amp;options) const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>get_substring_at_position</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8c696b6a4ee35a531b72cee9daf943b7</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>get_substring_with_length</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a575f8e3d2168ede51e7bc2cdd43fd7a1</anchor>
      <arglist>(size_t length) const</arglist>
    </member>
    <member kind="function">
      <type>var::Vector&lt; StringView &gt;</type>
      <name>split</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a69ed49ce363917ffa86513ca31e8343a</anchor>
      <arglist>(StringView delimeters) const</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a2034f8b658dfef696c6cf9269e2cb83d</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a34496139406eea2a6ef8524eb285b3e4</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>acf7a6fa71525f3f4e071e13b35206f45</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a2100a15f3209078e6e94287cc2169dce</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a7f1d29a3a82614dceed884625d7d824e</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a13bbb8b83bc507b63ec72192b9d64d85</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aa176c26ac55aa67880c954200f73f655</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>abf071d35311c8188ffe9a96f9c6119fb</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a47f790dfc5a74f5a7c3e74567932c925</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>affd4e2f6af7d75e3d538197df396c633</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a84fab0a8a2a19167fab6790cc3243950</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>afae41f20d05e15ff4beaddbba2e7f9cb</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>accc9b2997b134a03eb07dedcd65f65c8</anchor>
      <arglist>(StringView a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8793b9413b8d30918c336f01e1b56f11</anchor>
      <arglist>(char a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_first_of</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a07622ee75293fbd1409e1da5db2b5120</anchor>
      <arglist>(StringView a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_first_not_of</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aca5493514f22a29ee06f6d78e9849cf8</anchor>
      <arglist>(StringView a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>reverse_find</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ab662f4990bf813319c953cbbb8687390</anchor>
      <arglist>(StringView a, size_t position=npos) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>reverse_find</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aa8182be11cd22479c998f31768bbdc63</anchor>
      <arglist>(char a, size_t position=npos) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_last_of</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a290f71116f355e4ef3824a549a1e134b</anchor>
      <arglist>(StringView a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_last_not_of</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8fc193a1d8b605128730197430134c6b</anchor>
      <arglist>(StringView a, size_t position=0) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>afc161b985e8a74a3835d862e83314d5f</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8c24b9b0bfb67e92fc84e648f60b4084</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a64c28ea8edf90e738009bf72b0a0273a</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a3cc2fb989bcfe71c96442cd644e419f0</anchor>
      <arglist>(const char *a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a06e891cc63f3d3cb52053139bf0103e4</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ac158ec36950154b71bd4aa91a4244bf1</anchor>
      <arglist>(const String &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ac549c828489b4b19ff7ec08bab3fb8de</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a035ca6bda6a537cf22dff27c879ce176</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a1c2ec4a17bdd294cd50203568746eac5</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>abaa051a621d1b1dad14eeb23d9f71f43</anchor>
      <arglist>(const StringView a) const</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>to_long</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a266c527f980d1c3bfbfc832cef4c8169</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>to_float</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ac4a90a2b72185274be67298bd36f4924</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>to_unsigned_long</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a0969427e974af0c1ca60fa46bad8981e</anchor>
      <arglist>(Base base=Base::decimal) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>to_integer</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a34f4ed6d05053779dd6205f125853e59</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a7e522dd6cfdc6e9546dfc056b84babd9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>to_string</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>ab2d660f34159960f2dd3b7d006149428</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static String</type>
      <name>to_string</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a8ecb920e89880c8021001d9c432f68e6</anchor>
      <arglist>(const StringView &amp;a)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>constexpr static size_t</type>
      <name>npos</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>aa361886269517a46d938cf264d11f6cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>String</name>
      <anchorfile>classvar_1_1_string_view.html</anchorfile>
      <anchor>a7fb804f7dc96dd9f705c84095f37f1ca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::StringView::GetSubstring</name>
    <filename>classvar_1_1_string_view_1_1_get_substring.html</filename>
  </compound>
  <compound kind="class">
    <name>var::Tokenizer</name>
    <filename>classvar_1_1_tokenizer.html</filename>
    <base>api::ExecutionContext</base>
    <class kind="class">var::Tokenizer::Construct</class>
    <member kind="enumeration">
      <type></type>
      <name>SortBy</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a5580c0b12d9db7e3fa60569f0b5b347f</anchor>
      <arglist></arglist>
      <enumvalue file="classvar_1_1_tokenizer.html" anchor="a5580c0b12d9db7e3fa60569f0b5b347fa334c4a4c42fdb79d7ebc3e73b517e6f8">none</enumvalue>
      <enumvalue file="classvar_1_1_tokenizer.html" anchor="a5580c0b12d9db7e3fa60569f0b5b347fa9c9ab624360885fcf93b7643c93b6748">ascending</enumvalue>
      <enumvalue file="classvar_1_1_tokenizer.html" anchor="a5580c0b12d9db7e3fa60569f0b5b347fab19e9805fd7727c52ca04dfa3d24a2e5">descending</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>Tokenizer</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a1bc501fc04e95957e08c9c3bdfb10fe6</anchor>
      <arglist>(StringView input, const Construct &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Tokenizer &amp;</type>
      <name>sort</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a685b9295b02cb02882e2414a28613e46</anchor>
      <arglist>(SortBy sort_option)</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a7f620d5817548ef23eb52a1220e2c165</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>StringView</type>
      <name>at</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>af5553ea65110cb43e8b6da3af1a68572</anchor>
      <arglist>(u32 n) const</arglist>
    </member>
    <member kind="function">
      <type>const StringViewList &amp;</type>
      <name>list</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a6147456e03fd711e6c47330929f91ff1</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>join</name>
      <anchorfile>classvar_1_1_tokenizer.html</anchorfile>
      <anchor>a708036b6ed58d1742702330e5783bd63</anchor>
      <arglist>(StringView delimeter) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Tokenizer::Construct</name>
    <filename>classvar_1_1_tokenizer_1_1_construct.html</filename>
  </compound>
  <compound kind="class">
    <name>var::Transformer</name>
    <filename>classvar_1_1_transformer.html</filename>
    <class kind="class">var::Transformer::Transform</class>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>transform</name>
      <anchorfile>classvar_1_1_transformer.html</anchorfile>
      <anchor>a88dc136e9d743e4f45b84a7bf71ec9b0</anchor>
      <arglist>(const Transform &amp;options) const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>get_output_size</name>
      <anchorfile>classvar_1_1_transformer.html</anchorfile>
      <anchor>a437a1e4036b38537097032ec8ca8078c</anchor>
      <arglist>(size_t nbyte) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_t</type>
      <name>page_size_boundary</name>
      <anchorfile>classvar_1_1_transformer.html</anchorfile>
      <anchor>a55ecc895b99b5ffab1942c90dcd4d1a7</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Transformer::Transform</name>
    <filename>classvar_1_1_transformer_1_1_transform.html</filename>
  </compound>
  <compound kind="class">
    <name>var::Vector</name>
    <filename>classvar_1_1_vector.html</filename>
    <templarg>typename T</templarg>
    <base>api::ExecutionContext</base>
    <class kind="class">var::Vector::Erase</class>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::iterator</type>
      <name>iterator</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>afeae257297891ce498fb91fbe302e2ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a6644b0c4018a3f02ee5027cfe1e11289</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::reverse_iterator</type>
      <name>reverse_iterator</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3fd02c58167fbae6c6ab4d741a3d9dc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename std::vector&lt; T &gt;::const_reverse_iterator</type>
      <name>const_reverse_iterator</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a53869f37cfb488d56cb150697ba3fd5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool(*</type>
      <name>sort_compartor_t</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a439117b131f89c5088ecc0584dad7393</anchor>
      <arglist>)(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a172af766d48830f1de444f1adca3578a</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>af8808b449967ecfc3b9612a71e6e0cdf</anchor>
      <arglist>(size_t count)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>aeaaf24bf6a46675fb3c3f2ee4c11b5b3</anchor>
      <arglist>(std::initializer_list&lt; T &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>operator=</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a5fcd5ddfbff848388212693802471ab2</anchor>
      <arglist>(std::initializer_list&lt; T &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a86bee2965cfd646f3e2b8a1faf2ef86a</anchor>
      <arglist>(const T &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a00e89c3db03c4485fc0532c1b751f6f1</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>begin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>abb4dd6fc874de15120659f53b1370972</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a02c4845e29ae0fdd1f24e2ff498d43e4</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>end</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>add304a650b30f38b913f0bd48ee3666d</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cbegin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>af81a0b6fc5bf5d911b5059857ede9490</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>cend</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a53e2e21a45962cbabe9bf7c84e15a4ac</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a669e660fa3fa36815f59af1e160b5233</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rbegin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ade775f6efc1a8fb4b7514bca8c26b351</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3de948c1c703cf68b350a25986a4542a</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>reverse_iterator</type>
      <name>rend</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ad41b6dc48a16a4c20a07ae896567c095</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crbegin</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a557d6ada72b764854f93f2784bd91508</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>const_reverse_iterator</type>
      <name>crend</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a42e88c96fac12beba9d08ea1c7a7c739</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a183026b33e1fab97c8fca12a77b167a0</anchor>
      <arglist>(const_iterator position, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a99f287c34140d4d0fb2e3695bdf08393</anchor>
      <arglist>(size_t position, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a89581fbc299d871518ac58d591574db5</anchor>
      <arglist>(const_iterator position, size_t n, const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a68a985075dad781039dd6ca613eac08a</anchor>
      <arglist>(const_iterator position, T &amp;&amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ae8b876774e2e39461cc0b6702f8a4955</anchor>
      <arglist>(size_t position, T &amp;&amp;value)</arglist>
    </member>
    <member kind="function">
      <type>iterator</type>
      <name>insert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a2b12e27090b63905094d1c621e92b36f</anchor>
      <arglist>(const_iterator position, std::initializer_list&lt; T &gt; il)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>afe7829b4ebe1706bda3af27802f483b3</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3b4633a5b17129e9d224aafd9dca3db4</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>af59e129c81e06fed60aca29332d9086d</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a9a2f0633fab9dd8e5b944893e6c4eb63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>back</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ae1edc4922bf54b0921dcfad608ea8435</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a121d88485a2977c5cf911d16a29d242f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>front</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a61e902b60f1cbf090a936d2c2455c985</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>push_back</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a91819913e5e50e01098a851f8b75e457</anchor>
      <arglist>(const T &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a4ba16747aae0da1e32a28cd450ad543b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>shrink_to_fit</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ac1e6f86bb35e925887c628be78a1cc41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>erase</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ac108db2ce3610eaaf193ad14bc44e934</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>operator()</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a50154ea55a12f619b61d20e5e0eced48</anchor>
      <arglist>(const Erase &amp;options)</arglist>
    </member>
    <member kind="function">
      <type>Vector &amp;</type>
      <name>remove</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a50d806fd6b9f1d64610bdcbb00a88ba1</anchor>
      <arglist>(u32 pos)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a45a12afce67e0acfab40ba90963fff0c</anchor>
      <arglist>(size_t offset) const</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator[]</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a72f43759dd284cc82104d05795caca0d</anchor>
      <arglist>(size_t offset)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_offset</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a85072adfb49e3b218423a4581d1d980e</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>find</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a59fb478f07447b7a716fb1eb271ecd00</anchor>
      <arglist>(const T &amp;a, const T &amp;not_found=T()) const</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>search</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a6b4f9803264993553b7ca7c75ac65bdd</anchor>
      <arglist>(const T &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>search</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a9c4c804bed735b989836f30dea1b2952</anchor>
      <arglist>(const T &amp;a, int(*compare)(const void *, const void *))</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>fill</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>abba7af61432f82cdc9b6fc7fb222716f</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>resize</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a0664ef0f058714b0a286dd489e9b289c</anchor>
      <arglist>(size_t count)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>reserve</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a50b9aaf8fd0aea874e55a5d3261b27b1</anchor>
      <arglist>(size_t count)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>free</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a9c2d72482742907b24198361a5d93864</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; ConvertedType &gt;</type>
      <name>convert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3ce33bb1e775ef3c31e381755a572474</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; ConvertedType &gt;</type>
      <name>convert</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a738bcf3097b3c133558a5daa7232425b</anchor>
      <arglist>(ConvertedType(*convert_function)(const T &amp;value)) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>sort</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a2154e4235019e73139891dbdee8153ad</anchor>
      <arglist>(sort_compartor_t compare_function)</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>count</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a87820353bc78ab065ff2b8bee485e3cf</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator+</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a705cf671f0eeae3d86230dae36f98741</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator-</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a40cb313cac6824984ec268ceafdf5709</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a9e77ca4066cd80b43664ce337d3887f1</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator/</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3bb733b8ff11e003e9e5657446bc7b4c</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator+</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a332cb9f890277bb4b6e63ab4dcf0f3c6</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator-</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ae52640c6821d654ef654029f493c739f</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator*</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a7cb57f2fa59b292d6ca16339f67d9b2f</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator/</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a52b8b18e0b7a1e5592446c31a9350142</anchor>
      <arglist>(const T &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>aab633dd4a96d7c25249362f0360206cf</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a1f854409d527859efd15e7afeca5f612</anchor>
      <arglist>(u32 a) const</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; T &gt; &amp;</type>
      <name>clear</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a96e0bae3dfba659d2ef9e258bd36df52</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>aba68eb3047a7bc12c4bf4132b336b2ff</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; T &gt; &amp;</type>
      <name>vector</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a51ff92b0580664155bfe90a8e0edbf77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; T &gt; &amp;</type>
      <name>vector</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ae3c6212411dd462786dbc37bc3114405</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>afd32ee0dfb078a14eac838642a032507</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a0154c1ce8e553d8c7473e9c4331358fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>to_void</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a3bc28585168c4e0b0216f2f17f08bbed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>to_const_void</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a59fc065b50ac8176b82c3f694ba5ff6f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>accumulate</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>aedb8ddc655128f68f2e79376ae66fa92</anchor>
      <arglist>(T initial_value=T()) const</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>sum</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a7140de363129c77fd2fa5a49c9d57be7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>mean</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a0b5bd0b587e1edf2015449546781e061</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>variance</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a13febf3b885c65d4b2bd818c509ba740</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ascending</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ac9374b1cd28b7193245321779ba4134d</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>descending</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a059b8880b8db6236be83abdfba255118</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Vector&lt; T &gt;</type>
      <name>operate</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ac386015ba3f94383efbe669d25a93335</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a, T(*fn)(const T &amp;, const T &amp;)) const</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Vector&lt; T &gt;</type>
      <name>operate_single</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a2b1aefc6a123b3837b3a0caac928b3f8</anchor>
      <arglist>(const T &amp;a, T(*fn)(const T &amp;, const T &amp;)) const</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static T</type>
      <name>add</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>ae5ef9840d3b60948a6e5a7294f55bd18</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static T</type>
      <name>subtract</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a07701006279bb744b08ed4e9d46f2131</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static T</type>
      <name>multiply</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>aa482505ea1ac8184d31d69ebb74b9d92</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static T</type>
      <name>divide</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>acecaad85bb6ec92a0161a60b8b99241d</anchor>
      <arglist>(const T &amp;a, const T &amp;b)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static bool</type>
      <name>compare</name>
      <anchorfile>classvar_1_1_vector.html</anchorfile>
      <anchor>a5f69aa6e50e80c8535364c1a355b62d5</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;a, const Vector&lt; T &gt; &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>var::Vector::Erase</name>
    <filename>classvar_1_1_vector_1_1_erase.html</filename>
  </compound>
  <compound kind="class">
    <name>var::View</name>
    <filename>classvar_1_1_view.html</filename>
    <base>api::ExecutionContext</base>
    <member kind="enumeration">
      <type></type>
      <name>SwapBy</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aed6d6f2049d75037f686f29019a02070</anchor>
      <arglist></arglist>
      <enumvalue file="classvar_1_1_view.html" anchor="aed6d6f2049d75037f686f29019a02070a55d85f764eb26107897ed9adf70d05cf">half_word</enumvalue>
      <enumvalue file="classvar_1_1_view.html" anchor="aed6d6f2049d75037f686f29019a02070ac47d187067c6cf953245f128b5fde62a">word</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a389f08508c5183e18d7280fd0c91606f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>acd854ce1e2f3cfe40a4d3eb8f385df16</anchor>
      <arglist>(const Data &amp;data)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a5cbd661362f8eb6e814bca2bdd6cde8a</anchor>
      <arglist>(Data &amp;data)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a9d9f2da8f0d062006507960b04c9ca8f</anchor>
      <arglist>(const char *str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a2d99dcaa5846d8bf8a485bfed12ef50f</anchor>
      <arglist>(StringView str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a3b62e2554f3e0b453859c1cb0cbdb70d</anchor>
      <arglist>(const String &amp;str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aeaf3a9d90ea516d888d51716c01e949f</anchor>
      <arglist>(String &amp;str)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a0a6dc9fb1f869eed625bce1faaf95f7c</anchor>
      <arglist>(const void *buffer, size_t size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ae92baa6384f848c6854d22a37afc29c4</anchor>
      <arglist>(void *buffer, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>StringType</type>
      <name>to_string</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aca1e3f284c1d4c67101d190b4f577026</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a574f684ecacfe76cc7a90937a0ac1400</anchor>
      <arglist>(const Vector&lt; T &gt; &amp;vector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a59dc83b9646854de46e5e80ea847d4de</anchor>
      <arglist>(Vector&lt; T &gt; &amp;vector)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a8b92661e3f7b0c0c7e39328528a6f7dd</anchor>
      <arglist>(const Array&lt; T, size_value &gt; &amp;array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a16945bb0ea5e97acf60779c60eee82ec</anchor>
      <arglist>(Array&lt; T, size_value &gt; &amp;array)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>View</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ad236496dfa47dd94700f80ec53b7b954</anchor>
      <arglist>(T &amp;item)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_valid</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a651f51b652625476962f7da8310df0f5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_null</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a34f5497fa6a220160bb2af0a6a2deaf5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>fill</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a5b49fdfcc6ecfea397bff924d2278b23</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find_offset</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>acddb76d2656032665480200674a19ccc</anchor>
      <arglist>(const T &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>find</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a96172aee98c82fe33a71f517db9d9c5d</anchor>
      <arglist>(const View &amp;view, size_t alignment=1) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>count</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aa331cccc372ee08a448e6999b41b3a93</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>verify_zero_sum</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a23ab5776de9a6df4b6f30cafe39a3ce7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>swap_byte_order</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>adc3a4d268a58d506fc1163a649fd2c7a</anchor>
      <arglist>(SwapBy order)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aa07303d7fcef97ae2b6442ca23097160</anchor>
      <arglist>(const View &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a981d1a602fef54515c367fce94e55ccb</anchor>
      <arglist>(const View &amp;a) const</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>size</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aaf8353c18c8cf0f5768f253cb925d265</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>truncate</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a153f98d613c98fac8cbecc685758c585</anchor>
      <arglist>(size_t new_size)</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>pop_back</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a4947efb107839bd56d8f28bc913e9a10</anchor>
      <arglist>(size_t pop_size=1)</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>pop_front</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a524b1fe5e1ceebf0691d5e7103feaaa3</anchor>
      <arglist>(size_t pop_size=1)</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>size_signed</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a0d048d9e47240e612e63241b71df48d2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>copy</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a6258242307d7bd18f089ddf43108df56</anchor>
      <arglist>(const View &amp;source)</arglist>
    </member>
    <member kind="function">
      <type>const T *</type>
      <name>to</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a4bdf97a021137d03924abb1d79d3c694</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>to</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a924b566df8ecfa6b3b7f78ae1db3ec58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>to_const_char</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ad2409b26b26415265be44a7a8be82f07</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>to_char</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a81d063a8423e6ca975ea2f4a99d3c51f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>to_const_void</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a3287e4a1caa68011d3a138c0da0c2d93</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>to_void</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a9bcde9bc2773ed273f87770d93d8fae1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const u8 *</type>
      <name>to_const_u8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a956708647db6128750b562ebaa749187</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u8 *</type>
      <name>to_u8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a408e9c265cc313f3201f17e63be49577</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const u16 *</type>
      <name>to_const_u16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a33f3d4301315e3d6f730c746aedb60f6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u16 *</type>
      <name>to_u16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a1952af2390af67ef168775539a2c1357</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const u32 *</type>
      <name>to_const_u32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>aeb3f32cbc0481f9eda66d838464dd373</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u32 *</type>
      <name>to_u32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ae00f625d068a41cb5ae63ac42f12d9ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const u64 *</type>
      <name>to_const_u64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a2bfa78cbc60e95d10065d74c8c49daef</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>u64 *</type>
      <name>to_u64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a2d2a3dd241133431c2b8530a7a6e23a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const s8 *</type>
      <name>to_const_s8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a491d4d139f34b2b2f7a0208da1ebb63f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>s8 *</type>
      <name>to_s8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>acd8096a01e075042d00a0152bb80ba87</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const s16 *</type>
      <name>to_const_s16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>adac66dcdda0a79940ee5917a5c00a6d0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>s16 *</type>
      <name>to_s16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ad774fb85455970d83ed2f457f36b1aad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const s32 *</type>
      <name>to_const_s32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a4c695425b82c7e2da61aed0579260ab5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>s32 *</type>
      <name>to_s32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a6ac185ab64411a6e7b0b0fc77aab1de8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const s64 *</type>
      <name>to_const_s64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ac0bc0a572f95f3c5ddfd9e44f2338c19</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>s64 *</type>
      <name>to_s64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a296951501395dc5ea27c8898ae13d171</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const float *</type>
      <name>to_const_float</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a44ab50ab32ebc55b4d3283db6efcfbc3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float *</type>
      <name>to_float</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a6b9d3a9e1789420a92eade402b4bcbb8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a53d3bb101e5ca3221497b9d9a52404be</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>at</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a4f3467d5bbf99630e14f7e6c2dd1acde</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>at_const_char</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ab2204a5ae7d21a090ed96306f4aa3455</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>char &amp;</type>
      <name>at_char</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a60e6926049303bd66fc33f37df67fb2c</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>u8</type>
      <name>at_const_u8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a97f9d4be07b159fa4c37ba9e81a9b2af</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>u8 &amp;</type>
      <name>at_u8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>abd814413beee2b495ec77dda30ef180f</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>u16</type>
      <name>at_const_u16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ae11d42b5497a99d3881317f83755e513</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>u16 &amp;</type>
      <name>at_u16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a723be64783a01c2e6497cc46ffd783e1</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>u32</type>
      <name>at_const_u32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a3d360de292a8d14fca086bc0a3c223fd</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>u32 &amp;</type>
      <name>at_u32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a1099d95b35c7fc2fc75234832a3c6935</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>u64</type>
      <name>at_const_u64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>affcc77be21f1e8982072bddc7a251679</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>u64 &amp;</type>
      <name>at_u64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ace09bf92f76a6eb6f72d2531bd8da232</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>s8</type>
      <name>at_const_s8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a77c329ff939cd9d832fe7ac839f3eb3f</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>s8 &amp;</type>
      <name>at_s8</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a69f8e01d9f23f26f1c8bd776b0d3f49d</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>s16</type>
      <name>at_const_s16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a017bcddcdb1525589705bdf16ffdcc50</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>s16 &amp;</type>
      <name>at_s16</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a95a2c61b1c4ce29eed5511ce1274401d</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>s32</type>
      <name>at_const_s32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ac905e1fd443b752d48beb10e71bb2ec7</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>s32 &amp;</type>
      <name>at_s32</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ae0561f08c46e4ca25bb5b806749ce1bd</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>s64</type>
      <name>at_const_s64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ab552d2199fee45deac23b2e655ea9d6d</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>s64 &amp;</type>
      <name>at_s64</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a7f5d492b4a7f34fb1b653f36ec3d767c</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>at_const_float</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>afa9e3a7e8ec6e44afb54ff5e6e02575f</anchor>
      <arglist>(size_t position) const</arglist>
    </member>
    <member kind="function">
      <type>float &amp;</type>
      <name>at_float</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>abc29f9bce47fa06c6de4143966b652d4</anchor>
      <arglist>(size_t position)</arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a6be0b42165b549165a1744e6dbdf2ebe</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>data</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>ad387f237373800618d052119bbbf9ec2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>View &amp;</type>
      <name>from_string</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a41bc41f0b6da6255216576539ba0154c</anchor>
      <arglist>(StringView value)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>constexpr static size_t</type>
      <name>npos</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a6afd03c34df6e98697c54bf5a24e4564</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_view</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a87374da412d44bc6c312104ea95c3c90</anchor>
      <arglist>(void *buffer, size_t size)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_view</name>
      <anchorfile>classvar_1_1_view.html</anchorfile>
      <anchor>a046c8e528d78acc7d5057f7eabbb9dd6</anchor>
      <arglist>(const void *buffer, size_t size)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>api</name>
    <filename>namespaceapi.html</filename>
    <class kind="class">api::Api</class>
    <class kind="class">api::ApiInfo</class>
    <class kind="class">api::Demangler</class>
    <class kind="class">api::Error</class>
    <class kind="class">api::ErrorGuard</class>
    <class kind="class">api::ExecutionContext</class>
    <class kind="class">api::Index</class>
    <class kind="class">api::IndexIterator</class>
    <class kind="class">api::PrivateExecutionContext</class>
    <class kind="class">api::ProgressCallback</class>
    <class kind="class">api::Range</class>
    <class kind="class">api::RangeIterator</class>
    <class kind="class">api::ThreadExecutionContext</class>
    <member kind="typedef">
      <type>ErrorGuard</type>
      <name>ErrorContext</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>a50bccdd6a269a17ad69000a3acabfa04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ErrorGuard</type>
      <name>ErrorScope</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>a4efe504e63365f31261ab7c97d2047e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const void *</type>
      <name>kernel_request_api</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>afafed9fab17d151041a76c41cec415fb</anchor>
      <arglist>(u32 request)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>api_assert</name>
      <anchorfile>namespaceapi.html</anchorfile>
      <anchor>abdebff78cb996a8397e5241439324f83</anchor>
      <arglist>(bool value, const char *function, int line)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>chrono</name>
    <filename>namespacechrono.html</filename>
    <class kind="class">chrono::ClockTime</class>
    <class kind="class">chrono::ClockTimer</class>
    <class kind="class">chrono::Date</class>
    <class kind="class">chrono::DateTime</class>
    <class kind="class">chrono::MicroTime</class>
    <class kind="class">chrono::PerformanceScope</class>
    <member kind="typedef">
      <type>PerformanceScope</type>
      <name>PerformanceContext</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>aa19019b31230c5f70b1d59edf342b762</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>u32</type>
      <name>micro_time_t</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>af2672f65e28905521c580f1afd434ccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>MicroTime</type>
      <name>Microseconds</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>ad9ceb98c3a90f286f34d6b3ccdae19ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a47ce77951f9fff5e63d761fed3eeb4d8</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>aae876c39b8ee9c3b991b140b715c7a06</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a97fa542653ca96e6435d08ea58e08075</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>abbb697846f030df0ff4b1dfc2f2a787e</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a7a6da1efdfb4c4306c46e0275d6a572f</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a9053dd7d642e4c2353e110d24dd2a80c</anchor>
      <arglist>(const ClockTimer &amp;lhs, const MicroTime &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a638ad5c45140bb7dd8cdf0e6f8dbe167</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a7675e764345b0bd9e2b7751569bc7067</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a99ccee7dc7fe7a64e57d6a36173f1ae8</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a597f19e7274671f78b6921e35388b87b</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a79bc778aba26f8bf0e7865a26a700366</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a9436b14ef69a0c04b2462988d8389ff2</anchor>
      <arglist>(const MicroTime &amp;lhs, const ClockTimer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wait</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>a62492efc5b45b282bd59f32199474c42</anchor>
      <arglist>(const MicroTime &amp;duration)</arglist>
    </member>
    <member kind="function">
      <type>MicroTime</type>
      <name>operator*</name>
      <anchorfile>namespacechrono.html</anchorfile>
      <anchor>af9713261d7d761bcffa80de8814c4f33</anchor>
      <arglist>(u32 lhs, MicroTime rhs)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fs</name>
    <filename>namespacefs.html</filename>
    <class kind="class">fs::Access</class>
    <class kind="class">fs::Aio</class>
    <class kind="class">fs::DataFile</class>
    <class kind="class">fs::Dir</class>
    <class kind="class">fs::DirAccess</class>
    <class kind="class">fs::DirObject</class>
    <class kind="class">fs::File</class>
    <class kind="class">fs::FileAccess</class>
    <class kind="class">fs::FileInfo</class>
    <class kind="class">fs::FileInfoFlags</class>
    <class kind="class">fs::FileMemberAccess</class>
    <class kind="class">fs::FileObject</class>
    <class kind="class">fs::FileSystem</class>
    <class kind="class">fs::LambdaFile</class>
    <class kind="class">fs::NullFile</class>
    <class kind="class">fs::OpenMode</class>
    <class kind="class">fs::Path</class>
    <class kind="class">fs::Permissions</class>
    <class kind="class">fs::ViewFile</class>
    <member kind="typedef">
      <type>var::Vector&lt; var::PathString &gt;</type>
      <name>PathList</name>
      <anchorfile>namespacefs.html</anchorfile>
      <anchor>a268f5f3572ece215c66853b85c003c33</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>hal</name>
    <filename>namespacehal.html</filename>
  </compound>
  <compound kind="namespace">
    <name>printer</name>
    <filename>namespaceprinter.html</filename>
    <class kind="class">printer::JsonPrinter</class>
    <class kind="class">printer::MarkdownPrinter</class>
    <class kind="class">printer::NullPrinter</class>
    <class kind="class">printer::Printer</class>
    <class kind="struct">printer::PrinterFlags</class>
    <class kind="class">printer::PrinterTermination</class>
    <class kind="class">printer::YamlPrinter</class>
    <member kind="function">
      <type>printer::Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a2532462d2ecf8d1bdb202902edef15fc</anchor>
      <arglist>(printer::Printer &amp;printer, const chrono::ClockTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a0026cc5e0ad54f38e57da9219a18ed93</anchor>
      <arglist>(Printer &amp;printer, const chrono::DateTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a5582f4fb098214f864c07489e1680ee7</anchor>
      <arglist>(Printer &amp;printer, const chrono::MicroTime &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a0ccb430b295e63492dbe238eeac1142b</anchor>
      <arglist>(Printer &amp;printer, const fs::FileInfo &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a3cc387ebf4e0d90ce8647c10a1d67f69</anchor>
      <arglist>(Printer &amp;printer, const fs::PathList &amp;a)</arglist>
    </member>
    <member kind="function">
      <type>Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespaceprinter.html</anchorfile>
      <anchor>a1b63fa4718f079fac972a1dcb316a522</anchor>
      <arglist>(Printer &amp;printer, const sys::Cli &amp;a)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>sys</name>
    <filename>namespacesys.html</filename>
    <class kind="class">sys::Cli</class>
    <class kind="class">sys::System</class>
    <class kind="class">sys::TemporaryDirectory</class>
    <class kind="class">sys::Version</class>
  </compound>
  <compound kind="namespace">
    <name>test</name>
    <filename>namespacetest.html</filename>
    <class kind="class">test::Case</class>
    <class kind="class">test::Function</class>
    <class kind="class">test::Test</class>
    <class kind="struct">test::TestFlags</class>
  </compound>
  <compound kind="namespace">
    <name>thread</name>
    <filename>namespacethread.html</filename>
    <class kind="class">thread::Cond</class>
    <class kind="class">thread::Mq</class>
    <class kind="class">thread::Mutex</class>
    <class kind="class">thread::Sched</class>
    <class kind="class">thread::SemAccess</class>
    <class kind="class">thread::Semaphore</class>
    <class kind="class">thread::SemaphoreObject</class>
    <class kind="class">thread::Signal</class>
    <class kind="class">thread::SignalFlags</class>
    <class kind="class">thread::SignalHandler</class>
    <class kind="class">thread::Thread</class>
    <class kind="class">thread::Timer</class>
    <class kind="class">thread::UnnamedSemaphore</class>
  </compound>
  <compound kind="namespace">
    <name>var</name>
    <filename>namespacevar.html</filename>
    <class kind="class">var::Array</class>
    <class kind="class">var::Base64</class>
    <class kind="class">var::Base64Decoder</class>
    <class kind="class">var::Base64Encoder</class>
    <class kind="class">var::Bits</class>
    <class kind="class">var::ContainerObject</class>
    <class kind="class">var::Data</class>
    <class kind="class">var::DataInfo</class>
    <class kind="class">var::Deque</class>
    <class kind="class">var::GeneralString</class>
    <class kind="class">var::IdString</class>
    <class kind="class">var::KeyString</class>
    <class kind="class">var::Matrix</class>
    <class kind="class">var::NameString</class>
    <class kind="class">var::NumberString</class>
    <class kind="class">var::Pair</class>
    <class kind="class">var::PathString</class>
    <class kind="class">var::Queue</class>
    <class kind="class">var::Ring</class>
    <class kind="class">var::Stack</class>
    <class kind="class">var::StackString</class>
    <class kind="class">var::String</class>
    <class kind="class">var::StringView</class>
    <class kind="class">var::Tokenizer</class>
    <class kind="class">var::Transformer</class>
    <class kind="class">var::Vector</class>
    <class kind="class">var::View</class>
    <member kind="typedef">
      <type>NumberString</type>
      <name>StackString64</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ab8da8f9be9708e0504562baa3f7bb09d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; String &gt;</type>
      <name>StringList</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ae6d46a5a5b3922626c34c5a470414ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Vector&lt; StringView &gt;</type>
      <name>StringViewList</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a6ecee59ce59f51bcc0a1189ed84d554a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Tokenizer</type>
      <name>Token</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a36f3577938a5e5a0d25122dcd2381ab9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>printer::Printer &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a5b203af4c63c908ff786a8d80e6e84ab</anchor>
      <arglist>(printer::Printer &amp;printer, const Matrix&lt; T &gt; &amp;matrix)</arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator&amp;</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a331680fd15fb1537023be86d5828513e</anchor>
      <arglist>(const StringView lhs, const StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>PathString</type>
      <name>operator/</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>ac5fc826094648ab7aab81bc04e47ef2d</anchor>
      <arglist>(const StringView lhs, const StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>GeneralString</type>
      <name>operator|</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a12affee639138783e9f32808d8770750</anchor>
      <arglist>(StringView lhs, StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>abe580a67cadc084787f83a9f43ff3481</anchor>
      <arglist>(StringView lhs, const String &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>aebbd64f7ea5551a91366045da8c81bb6</anchor>
      <arglist>(StringView lhs, StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>aeec2fc14c5a6bb40cfc239c02d524f08</anchor>
      <arglist>(const String &amp;lhs, StringView rhs)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>operator+</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a9c21e7bd6040c6f6d74c4081f3186dfe</anchor>
      <arglist>(StringView lhs, String &amp;&amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespacevar.html</anchorfile>
      <anchor>a92a73a6163a153697b1ae09ad7595f47</anchor>
      <arglist>(const char *lhs, StringView rhs)</arglist>
    </member>
  </compound>
</tagfile>
